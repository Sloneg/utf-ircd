/************************************************************************
 *   IRC - Internet Relay Chat, ircd/list.c
 *   Copyright (C) 1990 Jarkko Oikarinen and
 *                      University of Oulu, Finland
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "os.h"
#include "s_defines.h"
#define LIST_C
#include "s_externs.h"
#undef LIST_C

char *DefInfo = "*Not On This Net*"; /* constant */

#ifdef	DEBUGMODE
static	struct	liststats {
	int	inuse;
} cloc, crem, users, servs, links, classs, aconfs;

#endif

aServer	*svrtop = NULL;

int	numclients = 0;

void	initlists(void)
{
#ifdef	DEBUGMODE
	bzero((char *)&cloc, sizeof(cloc));
	bzero((char *)&crem, sizeof(crem));
	bzero((char *)&users, sizeof(users));
	bzero((char *)&servs, sizeof(servs));
	bzero((char *)&links, sizeof(links));
	bzero((char *)&classs, sizeof(classs));
	bzero((char *)&aconfs, sizeof(aconfs));
#endif
}

void	outofmemory()
{
	if (serverbooting)
	{

		fprintf(stderr,"Fatal Error: Out of memory.\n");
		exit(-1);
	}
	Debug((DEBUG_FATAL, "Out of memory: restarting server..."));
	sendto_flag(SCH_NOTICE, "Ouch!!! Out of memory...");
	server_reboot("Out of Memory");
}

#ifdef	DEBUGMODE
void	checklists()
{
	aServer	*sp;

	for (sp = svrtop; sp; sp = sp->nexts)
		if (sp->bcptr->serv != sp)
			Debug((DEBUG_ERROR, "svrtop: %#x->%#x->%#x != %#x",
				sp, sp->bcptr, sp->bcptr->serv, sp));
}
#endif
	
/*
** Create a new aClient structure and set it to initial state.
**
**	from == NULL,	create local client (a client connected
**			to a socket).
**
**	from,	create remote client (behind a socket
**			associated with the client defined by
**			'from'). ('from' is a local client!!).
*/
aClient	*make_client(aClient *from)
{
	Reg	aClient *cptr = NULL;
	Reg	unsigned size = (from) ? CLIENT_REMOTE_SIZE : CLIENT_LOCAL_SIZE;

	/*
	 * Check freelists first to see if we can grab a client without
	 * having to call malloc.
	 */
	if (!(cptr = (aClient *)MyMalloc(size)))
		outofmemory();
	bzero((char *)cptr, (int)size);

	/* Note:  structure is zero (calloc) */
	cptr->from = from ? from : cptr; /* 'from' of local client is self! */
	cptr->next = NULL; /* For machines with NON-ZERO NULL pointers >;) */
	cptr->prev = NULL;
	cptr->hnext = NULL;
	cptr->user = NULL;
	cptr->serv = NULL;
	cptr->status = STAT_UNKNOWN;
	cptr->fd = -1;
	(void)strcpy(cptr->username, "unknown");
	cptr->info = DefInfo;
	if (size == CLIENT_LOCAL_SIZE)
	    {
		cptr->since = cptr->lasttime = cptr->firsttime = timeofday;
		cptr->confs = NULL;
		cptr->sockhost[0] = '\0';
		cptr->buffer[0] = '\0';
		cptr->authfd = -1;
		cptr->auth = cptr->username;
		cptr->exitc = EXITC_UNDEF;
		cptr->receiveB = cptr->sendB = cptr->receiveM = cptr->sendM = 0;
#ifdef	HOLD_ENFORCED_NICKS
		cptr->held = 0;
#endif
#ifdef	ZIP_LINKS
		cptr->zip = NULL;
#endif
#ifndef USE_OLD8BIT
		cptr->conv = NULL;
#endif
#ifdef	DEBUGMODE
		cloc.inuse++;
	    }
	else
	    {
		crem.inuse++;
#endif
	    }
	return (cptr);
}

void	free_client(aClient *cptr)
{
	if (cptr->info != DefInfo)
		MyFree(cptr->info);
	if (MyConnect(cptr) && cptr->auth != cptr->username)
	{
	    sendto_flag(SCH_ERROR, "Please report to ircd-bug@irc.org about cptr->auth allocated but not free()d!");
		istat.is_authmem -= strlen(cptr->auth) + 1;
		istat.is_auth --;
		MyFree(cptr->auth);
	}
	MyFree(cptr);
}

/*
** 'make_user' add's an User information block to a client
** if it was not previously allocated.
*/
anUser	*make_user(aClient *cptr)
{
	Reg	anUser	*user;

	user = cptr->user;
	if (!user)
	    {
		user = (anUser *)MyMalloc(sizeof(anUser));
		memset(user, 0, sizeof(anUser));
#ifdef	DEBUGMODE
		users.inuse++;
#endif
		user->away = NULL;
		user->refcnt = 1;
		user->joined = 0;
		user->flags = 0;
		user->channel = NULL;
		user->invited = NULL;
		user->uwas = NULL;
		cptr->user = user;
		user->servp = NULL;
		user->bcptr = cptr;
		if (cptr->next)	/* the only cptr->next == NULL is me */
			istat.is_users++;
	    }
	return user;
}

aServer	*make_server(aClient *cptr)
{
	Reg	aServer	*serv = cptr->serv, *sp, *spp = NULL;

	if (!serv)
	    {
		serv = (aServer *)MyMalloc(sizeof(aServer));
		memset(serv, 0, sizeof(aServer));
#ifdef	DEBUGMODE
		servs.inuse++;
#endif
		cptr->serv = serv;
		serv->user = NULL;
		serv->snum = -1;
		*serv->by = '\0';
		*serv->tok = '\0';
		serv->stok = 0;
		serv->up = NULL;
		serv->refcnt = 1;
		serv->nexts = NULL;
		serv->prevs = NULL;
		
		for (sp = svrtop; sp; spp = sp, sp = sp->nexts)
			if (spp && ((spp->ltok) + 1 < sp->ltok))
				break;
		serv->prevs = spp;
		if (spp)
		    {
			serv->ltok = spp->ltok + 1;
			spp->nexts = serv;
		    }
		else
		    {	/* Me, myself and I alone */
			svrtop = serv;
			serv->ltok = 1;
		    }

		if (sp)
		    {
			serv->nexts = sp;
			sp->prevs = serv;
		    }
		serv->bcptr = cptr;
		sprintf(serv->tok, "%d", serv->ltok);
		serv->lastload = 0;
	    }
	return cptr->serv;
}

/*
** free_user
**	Decrease user reference count by one and release block,
**	if count reaches 0
*/
void	free_user(anUser *user)
{
	aServer *serv;
	aClient *cptr = user->bcptr;
	
	if (--user->refcnt <= 0)
	    {
		/* Loop: This would be second deallocation of this structure.
		 * XXX: Remove loop detection before 2.11.0 - jv
		 */

		if (user->refcnt == -211001)
		{
			sendto_flag(SCH_ERROR,
				"* %p free_user loop (%s!%s@%s) %p *",
				(void *)cptr, cptr ? cptr->name : "<noname>",
				user->username, user->host, user);

			return;
		}

		/*
		 * sanity check
		 */
		if (user->joined || user->refcnt < 0 ||
		    user->invited || user->channel || user->uwas ||
		    user->bcptr)
		{
			char buf[512];
			/*too many arguments for dumpcore() and sendto_flag()*/
			sprintf(buf, "%p %p %p %p %d %d %p (%s)",
				(void *)user, (void *)user->invited,
				(void *)user->channel, (void *)user->uwas,
				user->joined, user->refcnt,
				(void *)user->bcptr,
				(user->bcptr) ? user->bcptr->name :"none");
#ifdef DEBUGMODE
			dumpcore("%p user (%s!%s@%s) %s",
				(void *)cptr, cptr ? cptr->name : "<noname>",
				user->username, cptr->sockhost, buf);
#else
			sendto_flag(SCH_ERROR,
				"* %p user (%s!%s@%s) %s *",
				(void *)cptr, cptr ? cptr->name : "<noname>",
				user->username, cptr->sockhost, buf);
#endif
		}

		if ((serv = user->servp))
		{
			user->servp = NULL; /* to avoid some impossible loop */
			user->refcnt = -211000; /* For loop detection */
			free_server(serv);
		}

		if (user->away)
		{
			istat.is_away--;
			istat.is_awaymem -= (strlen(user->away) + 1);
			MyFree(user->away);
		}
		MyFree(user);
#ifdef	DEBUGMODE
		users.inuse--;
#endif
	    }

}

void	free_server(aServer *serv)
{
	aClient *cptr = serv->bcptr;
	/* decrement reference counter, and eventually free it */
	if (--serv->refcnt <= 0)
	    {
		if (serv->refcnt == -211001)
		{
			/* Loop detected, break it.
			 * XXX: Remove loop detection before 2.11.0 - jv */
			sendto_flag(SCH_DEBUG, "* %#x free_server loop %s *",
				    serv, cptr ? cptr->name : "<noname>");
			return;

		}
		/* Decrease (and possibly free) refcnt of the user struct
		 * of who connected this server.
		 */
		if (serv->user)
		{
			int cnt = serv->refcnt;
			serv->refcnt = -211000;	/* Loop detection */
			free_user(serv->user);
			serv->user = NULL;
			serv->refcnt = cnt;
		}
		
		if (serv->refcnt < 0 ||	serv->prevs || serv->nexts ||
		    serv->bcptr || serv->user)
		{
			char buf[512];

			sprintf(buf, "%d %p %p %p %p (%s)",
				serv->refcnt, (void *)serv->prevs,
				(void *)serv->nexts, (void *)serv->user,
				(void *)serv->bcptr,
				(serv->bcptr) ? serv->bcptr->name : "none");
#ifdef DEBUGMODE
			dumpcore("%#x server %s %s",
				 cptr, cptr ? cptr->name : "<noname>", buf);
			servs.inuse--;
#else
			sendto_flag(SCH_ERROR, "* %#x server %s %s *",
				    cptr, cptr ? cptr->name : "<noname>", buf);
#endif
		}

		MyFree(serv);
	    }
}

/*
 * taken the code from ExitOneClient() for this and placed it here.
 * - avalon
 * remove client **AND** _related structures_ from lists,
 * *free* them too. -krys
 */
void	remove_client_from_list(aClient *cptr)
{
	checklist();
	/* is there another way, at this point? */
	/* servers directly connected have hopcount=1, but so do their */
	/* users, hence the check for IsServer --B. */
	if (cptr->hopcount == 0 ||
		(cptr->hopcount == 1 && IsServer(cptr))) 
		istat.is_localc--;
	else
		istat.is_remc--;
	if (cptr->prev)
		cptr->prev->next = cptr->next;
	else
	    {
		client = cptr->next;
		client->prev = NULL;
	    }
	if (cptr->next)
		cptr->next->prev = cptr->prev;

	if (cptr->user)
	    {
		istat.is_users--;
		/* decrement reference counter, and eventually free it */
		cptr->user->bcptr = NULL;
		(void)free_user(cptr->user);
	    }

	if (cptr->serv)
	    {
		/* has to be removed from the list of aServer structures */
		if (cptr->serv->nexts)
			cptr->serv->nexts->prevs = cptr->serv->prevs;
		if (cptr->serv->prevs)
			cptr->serv->prevs->nexts = cptr->serv->nexts;
		if (svrtop == cptr->serv)
			svrtop = cptr->serv->nexts;
		cptr->serv->prevs = NULL;
		cptr->serv->nexts = NULL;
		
		if (cptr->serv->user)
		    {
			free_user(cptr->serv->user);
			cptr->serv->user = NULL;
		    }

		/* decrement reference counter, and eventually free it */
		cptr->serv->bcptr = NULL;
		free_server(cptr->serv);
	    }

	if (cptr->service)
		/*
		** has to be removed from the list of aService structures,
		** no reference counter for services, thus this part of the
		** code can safely be included in free_service()
		*/
		free_service(cptr);

#ifdef	DEBUGMODE
	if (cptr->fd == -2)
		cloc.inuse--;
	else
		crem.inuse--;
#endif

	(void)free_client(cptr);
	numclients--;
	return;
}

/*
 * move the client aClient struct before its server's
 */
void	reorder_client_in_list(aClient *cptr)
{
    if (cptr->user == NULL && cptr->service == NULL)
	    return;

    /* update neighbours */
    if (cptr->next)
	    cptr->next->prev = cptr->prev;
    if (cptr->prev)
	    cptr->prev->next = cptr->next;
    else
	    client = cptr->next;

    /* re-insert */
    if (cptr->user)
	{
	    cptr->next = cptr->user->servp->bcptr;
	    cptr->prev = cptr->user->servp->bcptr->prev;
/*#ifdef DEBUGMODE
	    sendto_flag(SCH_DEBUG, "%p [%s] moved before server: %p [%s]", 
			cptr, cptr->name, cptr->user->servp->bcptr, 
			cptr->user->servp->bcptr->name);
#endif*/
	}
    else if (cptr->service)
	{
	    cptr->next = cptr->service->servp->bcptr;
	    cptr->prev = cptr->service->servp->bcptr->prev;
	}

    /* update new neighbours */
    if (cptr->prev)
	    cptr->prev->next = cptr;
    else
	    client = cptr;
    cptr->next->prev = cptr;
}

/*
 * although only a small routine, it appears in a number of places
 * as a collection of a few lines...functions like this *should* be
 * in this file, shouldnt they ?  after all, this is list.c, isnt it ?
 * -avalon
 */
void	add_client_to_list(aClient *cptr)
{
	/*
	 * since we always insert new clients to the top of the list,
	 * this should mean the "me" is the bottom most item in the list.
	 */
	if (cptr->from == cptr)
		istat.is_localc++;
	else
		istat.is_remc++;
	if (cptr->user)
		istat.is_users++;
	
	cptr->next = client;
	client = cptr;
	
	if (cptr->next)
		cptr->next->prev = cptr;

	numclients++;
	return;
}

/*
 * Look for ptr in the linked listed pointed to by link.
 */
Link	*find_user_link(Link *lp, aClient *ptr)
{
	if (ptr)
		for (; lp; lp = lp->next)
			if (lp->value.cptr == ptr)
				return (lp);
	return NULL;
}

Link  *find_channel_link(Link *lp, aChannel *ptr)
{ 
	if (ptr)
		for (; lp; lp = lp->next)
			if (lp->value.chptr == ptr)
				return (lp);
	return NULL;    
}

Link	*make_link()
{
	Reg	Link	*lp;

	lp = (Link *)MyMalloc(sizeof(Link));
#ifdef	DEBUGMODE
	links.inuse++;
#endif
	lp->flags = 0;
	return lp;
}

void	free_link(Link *lp)
{
	MyFree(lp);
#ifdef	DEBUGMODE
	links.inuse--;
#endif
}


aClass	*make_class()
{
	Reg	aClass	*tmp;

	tmp = (aClass *)MyMalloc(sizeof(aClass));
#ifdef	DEBUGMODE
	classs.inuse++;
#endif
	return tmp;
}

void	free_class(tmp)
Reg	aClass	*tmp;
{
	MyFree(tmp);
#ifdef	DEBUGMODE
	classs.inuse--;
#endif
}

aConfItem	*make_conf(void)
{
	Reg	aConfItem *aconf;

	aconf = (struct ConfItem *)MyMalloc(sizeof(aConfItem));

#ifdef	DEBUGMODE
	aconfs.inuse++;
#endif
	istat.is_conf++;
	istat.is_confmem += sizeof(aConfItem);

	bzero((char *)&aconf->ipnum, sizeof(struct in_addr));
	aconf->clients = aconf->port = 0;
	aconf->next = NULL;
	aconf->host = aconf->passwd = aconf->name = NULL;
	aconf->ping = NULL;
	aconf->status = CONF_ILLEGAL;
	aconf->pref = -1;
	aconf->hold = time(NULL);
	Class(aconf) = NULL;
	return (aconf);
}

void	delist_conf(aConfItem *aconf)
{
	if (aconf == conf)
		conf = conf->next;
	else
	    {
		aConfItem	*bconf;

		for (bconf = conf; aconf != bconf->next; bconf = bconf->next)
			;
		bconf->next = aconf->next;
	    }
	aconf->next = NULL;
}

void	free_conf(aConfItem *aconf)
{
	del_queries((char *)aconf);

	istat.is_conf--;
	istat.is_confmem -= aconf->host ? strlen(aconf->host)+1 : 0;
	istat.is_confmem -= aconf->passwd ? strlen(aconf->passwd)+1 : 0;
	istat.is_confmem -= aconf->name ? strlen(aconf->name)+1 : 0;
	istat.is_confmem -= aconf->ping ? sizeof(*aconf->ping) : 0;
	istat.is_confmem -= sizeof(aConfItem);

	MyFree(aconf->host);
	if (aconf->passwd)
		bzero(aconf->passwd, strlen(aconf->passwd));
	if (aconf->ping)
		MyFree(aconf->ping);
	MyFree(aconf->passwd);
	MyFree(aconf->name);
	MyFree(aconf);
#ifdef	DEBUGMODE
	aconfs.inuse--;
#endif
	return;
}

#ifdef	DEBUGMODE
void	send_listinfo(aClient *cptr, char *name)
{
	int	inuse = 0, mem = 0, tmp = 0;

	sendto_one(cptr, ":%s %d %s :Local: inuse: %d(%d)",
		   me.name, RPL_STATSDEBUG, name, inuse += cloc.inuse,
		   tmp = cloc.inuse * CLIENT_LOCAL_SIZE);
	mem += tmp;
	sendto_one(cptr, ":%s %d %s :Remote: inuse: %d(%d)",
		   me.name, RPL_STATSDEBUG, name,
		   crem.inuse, tmp = crem.inuse * CLIENT_REMOTE_SIZE);
	mem += tmp;
	inuse += crem.inuse;
	sendto_one(cptr, ":%s %d %s :Users: inuse: %d(%d)",
		   me.name, RPL_STATSDEBUG, name, users.inuse,
		   tmp = users.inuse * sizeof(anUser));
	mem += tmp;
	inuse += users.inuse,
	sendto_one(cptr, ":%s %d %s :Servs: inuse: %d(%d)",
		   me.name, RPL_STATSDEBUG, name, servs.inuse,
		   tmp = servs.inuse * sizeof(aServer));
	mem += tmp;
	inuse += servs.inuse,
	sendto_one(cptr, ":%s %d %s :Links: inuse: %d(%d)",
		   me.name, RPL_STATSDEBUG, name, links.inuse,
		   tmp = links.inuse * sizeof(Link));
	mem += tmp;
	inuse += links.inuse,
	sendto_one(cptr, ":%s %d %s :Classes: inuse: %d(%d)",
		   me.name, RPL_STATSDEBUG, name, classs.inuse,
		   tmp = classs.inuse * sizeof(aClass));
	mem += tmp;
	inuse += classs.inuse,
	sendto_one(cptr, ":%s %d %s :Confs: inuse: %d(%d)",
		   me.name, RPL_STATSDEBUG, name, aconfs.inuse,
		   tmp = aconfs.inuse * sizeof(aConfItem));
	mem += tmp;
	inuse += aconfs.inuse,
	sendto_one(cptr, ":%s %d %s :Totals: inuse %d %d",
		   me.name, RPL_STATSDEBUG, name, inuse, mem);
}
#endif


void	add_fd(int fd, FdAry *ary)
{
	Debug((DEBUG_DEBUG,"add_fd(%d,%#x)", fd, ary));
	if (fd >= 0)
		ary->fd[++(ary->highest)] = fd;
}


int	del_fd(int fd, FdAry *ary)
{
	int	i;

	Debug((DEBUG_DEBUG,"del_fd(%d,%#x)", fd, ary));
	if ((ary->highest == -1) || (fd < 0))
		return -1;
	for (i = 0; i <= ary->highest; i++)
		if (ary->fd[i] == fd)
			break;
	if (i < ary->highest)
	    {
		ary->fd[i] = ary->fd[ary->highest--];
		return 0;
	    }
	else if (i > ary->highest)
		return -1;
	ary->highest--;
	return 0;
}
