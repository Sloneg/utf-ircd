/************************************************************************
 *   IRC - Internet Relay Chat, ircd/s_misc.c (formerly ircd/date.c)
 *   Copyright (C) 1990 Jarkko Oikarinen and
 *                      University of Oulu, Computing Center
 *
 *   See file AUTHORS in IRC package for additional names of
 *   the programmers.
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
#define S_MISC_C
#include "s_externs.h"
#undef S_MISC_C
#if defined(IRCD_CHANGE_LOCALE) && !defined(USE_OLD8BIT)
#include <locale.h>
#endif

#define	NAMELEN	HOSTLEN * 2 + USERLEN + 5

static	void	exit_one_client(aClient *,aClient *,aClient *,char *);

static	char	*months[] = {
	"January",	"February",	"March",	"April",
	"May",	        "June",	        "July",	        "August",
	"September",	"October",	"November",	"December"
};

static	char	*weekdays[] = {
	"Sunday",	"Monday",	"Tuesday",	"Wednesday",
	"Thursday",	"Friday",	"Saturday"
};

/*
 * stats stuff
 */
struct	stats	ircst, *ircstp = &ircst;

char	*date(clock) 
time_t	clock;
{
	static	char	buf[80], plus;
	Reg	struct	tm *lt, *gm;
	struct	tm	gmbuf;
	int	minswest;

	if (!clock) 
		time(&clock);
	gm = gmtime(&clock);
	bcopy((char *)gm, (char *)&gmbuf, sizeof(gmbuf));
	gm = &gmbuf;
	lt = localtime(&clock);

	minswest = (gm->tm_hour - lt->tm_hour) * 60 
		    + (gm->tm_min - lt->tm_min);	
	if (lt->tm_yday != gm->tm_yday)
	    {
		if ((lt->tm_yday > gm->tm_yday 
		    && lt->tm_year == gm->tm_year) 
		    || (lt->tm_yday < gm->tm_yday 
		    && lt->tm_year != gm->tm_year)) 
		    {
			minswest -= 24 * 60;
		    }
		else
		    {
			minswest += 24 * 60;
		    }
	    }

	plus = (minswest > 0) ? '-' : '+';
	if (minswest < 0)
		minswest = -minswest;

	(void)sprintf(buf, "%s %s %d %d -- %02d:%02d %c%02d:%02d",
		weekdays[lt->tm_wday], months[lt->tm_mon],lt->tm_mday,
		lt->tm_year + 1900, lt->tm_hour, lt->tm_min,
		plus, minswest/60, minswest%60);

	return buf;
}

/*
** check_registered_user is used to cancel message, if the
** originator is a server or not registered yet. In other
** words, passing this test, *MUST* guarantee that the
** sptr->user exists (not checked after this--let there
** be coredumps to catch bugs... this is intentional --msa ;)
**
** There is this nagging feeling... should this NOT_REGISTERED
** error really be sent to remote users? This happening means
** that remote servers have this user registered, althout this
** one has it not... Not really users fault... Perhaps this
** error message should be restricted to local clients and some
** other thing generated for remotes...
*/
int	check_registered_user(sptr)
aClient	*sptr;
{
	if (!IsRegisteredUser(sptr))
	    {
		sendto_one(sptr, err_str(ERR_NOTREGISTERED, "*"));
		return -1;
	    }
	return 0;
}

/*
** check_registered user cancels message, if 'x' is not
** registered (e.g. we don't know yet whether a server
** or user)
*/
int	check_registered(sptr)
aClient	*sptr;
{
	if (!IsRegistered(sptr))
	    {
		sendto_one(sptr, err_str(ERR_NOTREGISTERED, "*"));
		return -1;
	    }
	return 0;
}

/*
** check_registered_service cancels message, if 'x' is not
** a registered service.
*/
int	check_registered_service(sptr)
aClient	*sptr;
{
	if (!IsService(sptr))
	    {
		sendto_one(sptr, err_str(ERR_NOTREGISTERED, "*"));
		return -1;
	    }
	return 0;
}

/*
** get_client_xname
**      Return the name of the client for m_trace
**
**	Returns:
**	  "name[user@host]" if 'isop' is true or FLAGS_VHOST is unset;
**	  "name[user@vhost]" otherwise
**
** NOTE 1:
**	Watch out the allocation of "nbuf", if either sptr->name
**	or sptr->sockhost gets changed into pointers instead of
**	directly allocated within the structure...
**
** NOTE 2:
**	Function return either a pointer to the structure (sptr) or
**	to internal buffer (nbuf). *NEVER* use the returned pointer
**	to modify what it points!!!
*/
char	*get_client_xname(sptr, isop)
aClient *sptr;
int	isop;
{
	static char nbuf[HOSTLEN * 2 + USERLEN + 5];

	if (MyConnect(sptr))
	    {
#ifdef UNIXPORT
		if (IsUnixSocket(sptr))
			sprintf(nbuf, "%s[%s]", sptr->name, me.sockhost);
		else
#endif
		    {
			if (strcasecmp(sptr->name, sptr->sockhost))
				/* Show username for clients and
				 * ident for others.
				 */
				sprintf(nbuf, "%s[%.*s@%s]",
					sptr->name, USERLEN,
					IsPerson(sptr) ?
						sptr->user->username :
						sptr->auth,
					(!isop && HasVHost(sptr)) ?
					sptr->user->host : sptr->sockhost);
			else
				return sptr->name;
		    }
		return nbuf;
	    }
	return sptr->name;
}

/*
** get_client_name
**	Return the name of the client for various tracking and
**	admin purposes. The main purpose of this function is to
**	return the "socket host" name of the client, if that
**	differs from the advertised name (other than case).
**	But, this can be used to any client structure.
**
**	Returns:
**	"name[user@ip#.port]" if 'showip' is true;
**	"name[username@sockethost]", if name and sockhost are different and
**	showip is false; else
**	"name".
**
** NOTE 1:
**	Watch out the allocation of "nbuf", if either sptr->name
**	or sptr->sockhost gets changed into pointers instead of
**	directly allocated within the structure...
**
** NOTE 2:
**	Function return either a pointer to the structure (sptr) or
**	to internal buffer (nbuf). *NEVER* use the returned pointer
**	to modify what it points!!!
*/
char	*get_client_name(sptr, showip)
aClient *sptr;
int	showip;
{
	static char nbuf[NAMELEN];

	if (MyConnect(sptr))
	    {
#ifdef UNIXPORT
		if (IsUnixSocket(sptr))
		    {
			if (showip)
				sprintf(nbuf, "%s[%s]",
					sptr->name, sptr->sockhost);
			else
				sprintf(nbuf, "%s[%s]",
					sptr->name, me.sockhost);
		    }
		else
#endif
		    {
			if (showip)
				(void)snprintf(nbuf, NAMELEN, "%s[%.*s@%s]",
					sptr->name, USERLEN,
					(!(sptr->flags & FLAGS_GOTID)) ? "" :
					sptr->auth,
#ifdef INET6 
					      inetntop(AF_INET6,
						       (char *)&sptr->ip,
						       mydummy, MYDUMMY_SIZE)
#else
					      inetntoa((char *)&sptr->ip)
#endif
									);
			else
			    {
				if (strcasecmp(sptr->name, sptr->sockhost))
					/* Show username for clients and
					 * ident for others.
					 */
					snprintf(nbuf, NAMELEN, "%s[%.*s@%s]",
						sptr->name, USERLEN,
						IsPerson(sptr) ?
							sptr->user->username :
							sptr->auth,
						sptr->sockhost);
				else
					return sptr->name;
			    }
		    }
		return nbuf;
	    }
	return sptr->name;
}

char	*get_client_host(cptr)
aClient	*cptr;
{
	static char nbuf[NAMELEN];

	if (!MyConnect(cptr))
		return cptr->name;
	if (!cptr->hostp)
		return get_client_name(cptr, FALSE);
#ifdef UNIXPORT
	if (IsUnixSocket(cptr))
		sprintf(nbuf, "%s[%s]", cptr->name, ME);
	else
#endif
		(void)snprintf(nbuf, NAMELEN, "%s[%-.*s@%-.*s]",
			cptr->name, USERLEN,
			(!(cptr->flags & FLAGS_GOTID)) ? "" : cptr->auth,
			HOSTLEN, cptr->hostp->h_name);
	return nbuf;
}

/*
 * Form sockhost such that if the host is of form user@host, only the host
 * portion is copied.
 */
void	get_sockhost(cptr, host)
Reg	aClient	*cptr;
Reg	char	*host;
{
	Reg	char	*s;
	Reg	int	len;

	if ((s = (char *)index(host, '@')))
		s++;
	else
		s = host;

	Debug((DEBUG_DNS,"get_sockhost %s",s));

	/* now handle smart asses who play tricks with
	   their DNS servers to produce long hostnames --erra */
	len = strlen(s) - sizeof(cptr->sockhost);

	if (len > 0)
		s += len + 1;

#ifdef USE_LIBIDN
	/* now reach clearance with multibyte strings */
	while (mblen(s, 6) == -1)
		s++;
#endif
	/* it's safe to call strcpy here */
	strcpy(cptr->sockhost, s);
}

/*
 * Return wildcard name of my server name according to given config entry
 * --Jto
 */
char	*my_name_for_link(name, count)
char	*name;
Reg	int	count;
{
	static	char	namebuf[HOSTLEN];
	Reg	char	*start = name;

	if (count <= 0 || count > 5)
		return start;

	while (count-- && name)
	    {
		name++;
		name = (char *)index(name, '.');
	    }
	if (!name)
		return start;

	namebuf[0] = '*';
	(void)strncpy(&namebuf[1], name, HOSTLEN - 1);
	namebuf[HOSTLEN - 1] = '\0';

	return namebuf;
}

/*
 * Goes thru the list of locally connected servers (except cptr),
 * check if my neighbours can see the server "name" (or if it is hidden
 * by a hostmask)
 * Returns the number of marked servers
 */
int
mark_blind_servers (cptr, name)
aClient	*cptr;
char	*name;
{
	Reg	int		i, j = 0;
	Reg	aClient		*acptr;
	Reg	aConfItem	*aconf;
	
	for (i = fdas.highest; i >= 0; i--)
	{
		if (!(acptr = local[fdas.fd[i]]) || !IsServer(acptr))
			continue;
		if (acptr == cptr || IsMe(acptr))
		{
			acptr->flags &= ~FLAGS_HIDDEN;
			continue;
		}
		if ((aconf = acptr->serv->nline) &&
		    (match(my_name_for_link(ME, aconf->port), name) == 0))
		{
			acptr->flags |= FLAGS_HIDDEN;
			j++;
		}
		else
		{
			acptr->flags &= ~FLAGS_HIDDEN;
		}
	}
	return j;
}

/*
** exit_client
**	This is old "m_bye". Name  changed, because this is not a
**	protocol function, but a general server utility function.
**
**	This function exits a client of *any* type (user, server, etc)
**	from this server. Also, this generates all necessary prototol
**	messages that this exit may cause.
**
**   1) If the client is a local client, then this implicitly
**	exits all other clients depending on this connection (e.g.
**	remote clients having 'from'-field that points to this.
**
**   2) If the client is a remote client, then only this is exited.
**
** For convenience, this function returns a suitable value for
** m_function return value:
**
**	FLUSH_BUFFER	if (cptr == sptr)
**	0		if (cptr != sptr)
*/
int	exit_client(cptr, sptr, from, comment)
aClient *cptr;	/*
		** The local client originating the exit or NULL, if this
		** exit is generated by this server for internal reasons.
		** This will not get any of the generated messages.
		*/
aClient *sptr;	/* Client exiting */
aClient *from;	/* Client firing off this Exit, never NULL! */
char	*comment;	/* Reason for the exit */
    {
	Reg	aClient	*acptr;
	Reg	aClient	*next;
	Reg	aServer *asptr;
	char	comment1[HOSTLEN + HOSTLEN + 2];
	int	flags = 0;

	if (MyConnect(sptr))
	    {
		if (sptr->flags & FLAGS_KILLED)
		    {
			sendto_flag(SCH_LOCAL, "Killed: %s.",
				    get_client_name(sptr, TRUE));
			sptr->exitc = EXITC_KILL;
		    }

		sptr->flags |= FLAGS_CLOSING;
#if defined(EXTRA_NOTICES) && defined(CLIENT_NOTICES)
		if (IsPerson(sptr))
			sendto_flag(SCH_OPER, "Client disconnected: %s (%s) %s",
			    sptr->name, sptr->sockhost,
			    comment ? comment : "");
#endif
#ifdef LOG_EVENTS
		if (IsPerson(sptr))
		    {
			sendto_flog(sptr, EXITC_REG, sptr->user->username,
				    sptr->sockhost);
		    }
                else if (!IsService(sptr))
                {
                        if (sptr->exitc == '\0' || sptr->exitc == EXITC_REG)
                        {
                                sptr->exitc = EXITC_UNDEF;
                        }
                        sendto_flog(sptr, sptr->exitc,
                                    sptr->user && sptr->user->username ?
                                    sptr->user->username : "",
#ifdef UNIXPORT
                                    (IsUnixSocket(sptr)) ? me.sockhost :
#endif
                                    ((sptr->hostp) ? sptr->hostp->h_name :
                                     sptr->sockhost));
                }


#endif /* LOG_EVENTS */
		if (IsPerson(sptr))
			istat.is_myclnt--;
		else if (IsServer(sptr))
			istat.is_myserv--;
		else if (IsService(sptr))
			istat.is_myservice--;
		else 
			istat.is_unknown--;

		if (cptr != NULL && sptr != cptr)
			sendto_one(sptr, "ERROR :Closing Link: %s %s (%s)",
				   get_client_name(sptr,FALSE),
				   cptr->name, comment);
		else
			sendto_one(sptr, "ERROR :Closing Link: %s (%s)",
				   get_client_name(sptr,FALSE), comment);

		if (sptr->auth != sptr->username)
		    {
			istat.is_authmem -= strlen(sptr->auth) + 1;
			istat.is_auth -= 1;
			MyFree(sptr->auth);
			sptr->auth = sptr->username;
		    }
		/*
		** Currently only server connections can have
		** depending remote clients here, but it does no
		** harm to check for all local clients. In
		** future some other clients than servers might
		** have remotes too...
		** now, I think it harms big client servers... - krys
		**
		** Close the Client connection first and mark it
		** so that no messages are attempted to send to it.
		** (The following *must* make MyConnect(sptr) == FALSE!).
		** It also makes sptr->from == NULL, thus it's unnecessary
		** to test whether "sptr != acptr" in the following loops.
		*/
		close_connection(sptr);
#ifndef USE_OLD8BIT
		/* conversion was activated so uncount it */
		conv_free_conversion(sptr->conv);
#endif

		if (IsServer(sptr))
		    {
		/*
		** First QUIT all NON-servers which are behind this link
		**
		** Note	There is no danger of 'cptr' being exited in
		**	the following loops. 'cptr' is a *local* client,
		**	all dependants are *remote* clients.
		*/

		/* This next bit is a a bit ugly but all it does is take the
		** name of us.. me.name and tack it together with the name of
		** the server sptr->name that just broke off and puts this
		** together into exit_one_client() to provide some useful
		** information about where the net is broken.      Ian 
		*/
			(void)strcpy(comment1, ME);
			(void)strcat(comment1," ");
			(void)strcat(comment1, sptr->name);

			/* This will quit all the *users*, without checking the
			** whole list of clients.
			*/
			for (asptr = svrtop; asptr; asptr = (aServer *)next)
			    {
				next = (aClient *)asptr->nexts;
				if ((asptr->bcptr == NULL) ||
				    (asptr->bcptr->from != sptr
				     && asptr->bcptr != sptr))
					continue;
				/*
				** This version doesn't need QUITs to be
				** propagaged unless the remote server is
				** hidden (by a hostmask)
				*/
				flags = FLAGS_SPLIT;
				if (mark_blind_servers(NULL,
						       asptr->bcptr->name))
					flags |= FLAGS_HIDDEN;
				while (GotDependantClient(asptr->bcptr))
				    {
					acptr = asptr->bcptr->prev;
					acptr->flags |= flags;
                                        /*
                                        ** Lock nick due to split -kmale
                                        */
                                        lock_nick(acptr->name,sptr->name);
					exit_one_client(NULL, acptr, &me,
							comment1);
				    }
			    }
			/*
			** Second SQUIT all servers behind this link
			*/
			for (asptr = svrtop; asptr; asptr = (aServer *)next)
			    {
				next = (aClient *)asptr->nexts;
				if ((acptr = asptr->bcptr) &&
				    acptr->from == sptr)
				    {
					sendto_flag(SCH_SERVER,
						    "Sending SQUIT %s (%s)",
						    acptr->name, comment);
					exit_one_client(NULL, acptr, &me, ME);
				    }
			    }
		    } /* If (IsServer(sptr)) */
	    } /* if (MyConnect(sptr) */

 	if (IsServer(sptr) && GotDependantClient(sptr))
 	{
 		/*
		** generate QUITs locally when receiving a SQUIT
		** check for hostmasking.
 		*/
 		flags = FLAGS_SPLIT;
 		if (mark_blind_servers(cptr, sptr->name))
 			flags |= FLAGS_HIDDEN;

		if (IsServer(from))
			/* this is a guess */
			(void)strcpy(comment1, from->name);
		else
			/* this is right */
			(void)strcpy(comment1, sptr->serv->up->name);
 		(void)strcat(comment1, " ");
 		(void)strcat(comment1, sptr->name);

		while (GotDependantClient(sptr))
 		{
 			acptr = sptr->prev;
 			acptr->flags |= flags;
                        /*
                        ** Lock nick due to split -kmale
                        */
                        lock_nick(acptr->name,sptr->name);
			exit_one_client(cptr, acptr, &me, comment1);
 		}
 	}
 	
	/*
	** Try to guess from comment if the client is exiting
	** normally (KILL or issued QUIT), or if it is splitting
	** It requires comment for splitting users to be
	** "server.some.where splitting.some.where"
	*/
	comment1[0] = '\0';
	if (!IsServer(sptr) && ((sptr->flags & FLAGS_KILLED) == 0))
	    {
	        char *c = comment;
		int i = 0;
		while (*c && *c != ' ')
			if (*c++ == '.')
				i++;
		if (*c++ && i)
		    {
		        i = 0;
			while (*c && *c != ' ')
				if (*c++ == '.')
					i++;
			if (!i || *c)
				sptr->flags |= FLAGS_QUIT;
		    }
		else
			sptr->flags |= FLAGS_QUIT;

		if (sptr == cptr && !(sptr->flags & FLAGS_QUIT))
		    {
			/*
			** This will avoid nick delay to be abused by
			** letting local users put a comment looking
			** like a server split.
			*/
			strncpyzt(comment1, comment, HOSTLEN + HOSTLEN);
			strcat(comment1, " ");
			sptr->flags |= FLAGS_QUIT;
		    }
	    }
	
	if (IsServer(sptr) && (cptr == sptr))
		sendto_flag(SCH_SERVER, "Sending SQUIT %s (%s)",
			    cptr->name, comment);
	
	exit_one_client(cptr, sptr, from, (*comment1) ? comment1 : comment);
	return !cptr || cptr == sptr ? FLUSH_BUFFER : 0;
    }

/*
** Exit one client, local or remote. Assuming all dependants have
** been already removed, and socket closed for local client.
*/
static	void	exit_one_client(cptr, sptr, from, comment)
aClient *sptr;
aClient *cptr;
aClient *from;
char	*comment;
{
	Reg	aClient *acptr;
	Reg	int	i;
	Reg	Link	*lp;

	/*
	**  For a server or user quitting, propagage the information to
	**  other servers (except to the one where is came from (cptr))
	*/
	if (IsMe(sptr))
	    {
		sendto_flag(SCH_ERROR,
			    "ERROR: tried to exit me! : %s", comment);
		return;	/* ...must *never* exit self!! */
	    }
	else if (IsServer(sptr)) {
	 /*
	 ** Old sendto_serv_but_one() call removed because we now
	 ** need to send different names to different servers
	 ** (domain name matching)
	 */
		istat.is_serv--;
	 	for (i = fdas.highest; i >= 0; i--)
		    {
			Reg	aConfItem *aconf;

			if (!(acptr = local[fdas.fd[i]]) || !IsServer(acptr) ||
			    acptr == cptr || IsMe(acptr))
				continue;
			if ((aconf = acptr->serv->nline) &&
			    (match(my_name_for_link(ME, aconf->port),
				     sptr->name) == 0))
				continue;
			sendto_one(acptr, ":%s SQUIT %s :%s",
				   from->name, sptr->name, comment);
		    }
#ifdef	USE_SERVICES
		check_services_butone(SERVICE_WANT_SQUIT, sptr->name, sptr,
				      ":%s SQUIT %s :%s", from->name,
				      sptr->name, comment);
#endif
		(void) del_from_server_hash_table(sptr->serv);
	} else if (!IsPerson(sptr) && !IsService(sptr))
		    /*
		    ** This is condition for unauthorized and rejected
		    ** connections (servers and clients) logged elsewhere --erra
		    */
		;
	else if (sptr->name[0] && !IsService(sptr)) /* clean with QUIT... */
	    {
		/*
		** If this exit is generated from "m_kill", then there
		** is no sense in sending the QUIT--KILL's have been
		** sent instead.
		*/
		if ((sptr->flags & FLAGS_KILLED) == 0)
		    {
			if ((sptr->flags & FLAGS_SPLIT) == 0)
			    {
				sendto_serv_butone(cptr, ":%s QUIT :%s",
						   sptr->name, comment);
#ifdef	USE_SERVICES
				check_services_butone(SERVICE_WANT_QUIT|
						      SERVICE_WANT_RQUIT, 
						      (sptr->user) ?
						      sptr->user->server
						      : NULL, cptr,
						      ":%s QUIT :%s",
						      sptr->name, comment);
#endif
			    }
			else
			    {
				if (sptr->flags & FLAGS_HIDDEN)
					/* joys of hostmasking */
					for (i = fdas.highest; i >= 0; i--)
					{
						if (!(acptr =local[fdas.fd[i]])
						    || !IsServer(acptr)
						    || acptr == cptr
						    || IsMe(acptr))
							continue;
						if (acptr->flags &FLAGS_HIDDEN)
							sendto_one(acptr,
								":%s QUIT :%s",
								   sptr->name,
								   comment);
					}
#ifdef	USE_SERVICES
				check_services_butone(SERVICE_WANT_QUIT, 
					      (sptr->user) ? sptr->user->server
						      : NULL, cptr,
						      ":%s QUIT :%s",
						      sptr->name, comment);
#endif
			    }
		    }
		/*
		** If a person is on a channel, send a QUIT notice
		** to every client (person) on the same channel (so
		** that the client can show the "**signoff" message).
		** (Note: The notice is to the local clients *only*)
		*/
		if (sptr->user)
		    {
			u_int8_t	has_quit, is_killed;

			if (IsInvisible(sptr))
				istat.is_user[1]--;
			else
				istat.is_user[0]--;

			if (IsAnOper(sptr))
				istat.is_oper--;

                        sendto_common_channels(sptr, ":%s QUIT :%s",
						sptr->name, comment);

			if (!(acptr = cptr ? cptr : sptr->from))
				acptr = sptr;

			has_quit	= (sptr->flags & FLAGS_QUIT) ? 1 : 0;
			is_killed	= (sptr->flags & FLAGS_KILLED) ? 1 : 0;

			while ((lp = sptr->user->channel))
			    {
				aChannel *chptr = lp->value.chptr;
				/*
				** Mark channels from where remote chop left,
				** this will eventually lock the channel.
				** close_connection() has already been called,
				** it makes MyConnect == False - krys
				*/
				if (sptr != cptr)
				{
					if (*chptr->chname == '!')
					    {
						if (!has_quit && !is_killed)
							chptr->history =
								timeofday +
							LDELAYCHASETIMELIMIT;
					    }
					else if (
#ifndef BETTER_CDELAY
						 !has_quit && !is_killed &&
#endif
						 is_chan_op(sptr, chptr))
						chptr->history =
							timeofday +
							DELAYCHASETIMELIMIT;
				}

				if (IsAnonymous(chptr) && !IsQuiet(chptr))
					sendto_channel_butserv(chptr, sptr,
							":%s PART %s :None",
								sptr->name,
								chptr->chname);

				remove_user_from_channel(sptr, chptr);
			    }

			/* Clean up invitefield */
			while ((lp = sptr->user->invited))
				del_invite(sptr, lp->value.chptr);
				/* again, this is all that is needed */

			/* Add user to history */
#ifndef BETTER_NDELAY
			add_history(sptr, (has_quit) ? &me : NULL);
#else
			add_history(sptr, (sptr == cptr) ? &me : NULL);
#endif
			off_history(sptr);
		    }
	    }
	else if (sptr->name[0] && IsService(sptr))
	    {
		/*
		** If this exit is generated from "m_kill", then there
		** is no sense in sending the QUIT--KILL's have been
		** sent instead.
		*/
		if ((sptr->flags & FLAGS_KILLED) == 0)
		    {
			/*
			** A service quitting is annoying, It has to be sent
			** to connected servers depending on 
			** sptr->service->dist
			*/
			for (i = fdas.highest; i >= 0; i--)
			    {
				if (!(acptr = local[fdas.fd[i]])
				    || !IsServer(acptr) || acptr == cptr
				    || IsMe(acptr))
					continue;
				if (match(sptr->service->dist, acptr->name))
					continue;
				sendto_one(acptr, ":%s QUIT :%s", sptr->name,
					   comment);
			    }
		    }
#ifdef	USE_SERVICES
		check_services_butone(SERVICE_WANT_SERVICE, NULL, NULL,
				      ":%s QUIT :%s", sptr->name, comment);
#endif
		/* MyConnect(sptr) is always FALSE here */
		if (cptr == sptr)
			sendto_flag(SCH_NOTICE, "Service %s disconnected",
				    get_client_name(sptr, TRUE));
		sendto_flag(SCH_SERVICE, "Received QUIT %s from %s (%s)",
			    sptr->name, from->name, comment);
		istat.is_service--;
	    }

	if (sptr->flags & FLAGS_COLLMAP)
	{
		if (!MyConnect(sptr) && sptr->from)	/* it can't be local client */
			del_from_collision_map(sptr->name, sptr->from->serv->crc);
		else
			sendto_flag(SCH_ERROR, "Found local %s in collision map",
				sptr->name);
	}
	/* Remove sptr from the client list */
	if (del_from_client_hash_table(sptr) != 1)
	{
		Debug((DEBUG_ERROR, "%#x !in tab %s[%s] %#x %#x %#x %d %d %#x",
			sptr, sptr->name,
			sptr->from ? sptr->from->sockhost : "??host",
			sptr->from, sptr->next, sptr->prev, sptr->fd,
			sptr->status, sptr->user));
	}
	remove_client_from_list(sptr);
	return;
}

void	checklist()
{
	Reg	aClient	*acptr;
	Reg	int	i,j;

	if (!(bootopt & BOOT_AUTODIE))
		return;
	for (j = i = 0; i <= highest_fd; i++)
		if (!(acptr = local[i]))
			continue;
		else if (IsClient(acptr))
			j++;
	if (!j)
	    {
#ifdef	USE_SYSLOG
		syslog(LOG_WARNING,"ircd exiting: autodie");
#endif
		exit(0);
	    }
	return;
}

void	initstats()
{
	bzero((char *)&istat, sizeof(istat));
	istat.is_serv = 1;
	istat.is_remc = 1;	/* don't ask me why, I forgot. */
	bzero((char *)&ircst, sizeof(ircst));
}

void	tstats(cptr, name)
aClient	*cptr;
char	*name;
{
	Reg	aClient	*acptr;
	Reg	int	i;
	Reg	struct stats	*sp;
	struct	stats	tmp;

	sp = &tmp;
	bcopy((char *)ircstp, (char *)sp, sizeof(*sp));
	for (i = 0; i < MAXCONNECTIONS; i++)
	    {
		if (!(acptr = local[i]))
			continue;
		if (IsServer(acptr))
		    {
			sp->is_sbs += acptr->sendB;
			sp->is_sbr += acptr->receiveB;
			sp->is_sks += acptr->sendK;
			sp->is_skr += acptr->receiveK;
			sp->is_sti += timeofday - acptr->firsttime;
			sp->is_sv++;
			if (sp->is_sbs > 1023)
			    {
				sp->is_sks += (sp->is_sbs >> 10);
				sp->is_sbs &= 0x3ff;
			    }
			if (sp->is_sbr > 1023)
			    {
				sp->is_skr += (sp->is_sbr >> 10);
				sp->is_sbr &= 0x3ff;
			    }
		    }
		else if (IsClient(acptr))
		    {
			sp->is_cbs += acptr->sendB;
			sp->is_cbr += acptr->receiveB;
			sp->is_cks += acptr->sendK;
			sp->is_ckr += acptr->receiveK;
			sp->is_cti += timeofday - acptr->firsttime;
			sp->is_cl++;
			if (sp->is_cbs > 1023)
			    {
				sp->is_cks += (sp->is_cbs >> 10);
				sp->is_cbs &= 0x3ff;
			    }
			if (sp->is_cbr > 1023)
			    {
				sp->is_ckr += (sp->is_cbr >> 10);
				sp->is_cbr &= 0x3ff;
			    }
		    }
		else if (IsUnknown(acptr))
			sp->is_ni++;
	    }

	sendto_one(cptr, ":%s %d %s :accepts %lu refused %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_ac, sp->is_ref);
	sendto_one(cptr, ":%s %d %s :unknown: commands %lu prefixes %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_unco, sp->is_unpf);
	sendto_one(cptr, ":%s %d %s :nick collisions %lu unknown closes %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_kill, sp->is_ni);
	sendto_one(cptr, ":%s %d %s :wrong direction %lu empty %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_wrdi, sp->is_empt);
	sendto_one(cptr, ":%s %d %s :users without servers %lu ghosts N/A",
		   ME, RPL_STATSDEBUG, name, sp->is_nosrv);
	sendto_one(cptr, ":%s %d %s :numerics seen %lu mode fakes %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_num, sp->is_fake);
	sendto_one(cptr, ":%s %d %s :auth: successes %lu fails %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_asuc, sp->is_abad);
	sendto_one(cptr,":%s %d %s :local connections %lu udp packets %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_loc, sp->is_udpok);
	sendto_one(cptr,":%s %d %s :udp errors %lu udp dropped %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_udperr, sp->is_udpdrop);
	sendto_one(cptr,
   ":%s %d %s :link checks %lu passed %lu 15s/%lu 30s dropped %luSq/%luYg/%luFl",
		   ME, RPL_STATSDEBUG, name, sp->is_ckl, sp->is_cklq,
		   sp->is_cklok, sp->is_cklQ, sp->is_ckly, sp->is_cklno);
	if (sp->is_wwcnt)
		sendto_one(cptr, ":%s %d %s :whowas turnover %lu/%lu/%lu [%lu]",
			   ME, RPL_STATSDEBUG, name, sp->is_wwmt,
			   (u_int) (sp->is_wwt / sp->is_wwcnt), sp->is_wwMt,
			   KILLCHASETIMELIMIT);
	if (sp->is_lkcnt)
		sendto_one(cptr, ":%s %d %s :ndelay turnover %lu/%lu/%lu [%lu]",
			   ME, RPL_STATSDEBUG, name, sp->is_lkmt,
			   (u_int) (sp->is_lkt / sp->is_lkcnt), sp->is_lkMt,
			   DELAYCHASETIMELIMIT);
	sendto_one(cptr, ":%s %d %s :abuse protections %u strict %u", ME,
		   RPL_STATSDEBUG, name, (bootopt & BOOT_PROT) ? 1 : 0,
		   (bootopt & BOOT_STRICTPROT) ? 1 : 0);
#ifdef DELAY_CLOSE
	sendto_one(cptr, ":%s %d %s :delay close %lu total %lu",
		ME, RPL_STATSDEBUG, name, istat.is_delayclosewait,
		istat.is_delayclose);
#endif
	sendto_one(cptr, ":%s %d %s :Client - Server",
		   ME, RPL_STATSDEBUG, name);
	sendto_one(cptr, ":%s %d %s :connected %lu %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_cl, sp->is_sv);
	sendto_one(cptr, ":%s %d %s :bytes sent %lu.%luK %lu.%luK",
		   ME, RPL_STATSDEBUG, name,
		   sp->is_cks, sp->is_cbs, sp->is_sks, sp->is_sbs);
	sendto_one(cptr, ":%s %d %s :bytes recv %lu.%luK %lu.%luK",
		   ME, RPL_STATSDEBUG, name,
		   sp->is_ckr, sp->is_cbr, sp->is_skr, sp->is_sbr);
	sendto_one(cptr, ":%s %d %s :time connected %lu %lu",
		   ME, RPL_STATSDEBUG, name, sp->is_cti, sp->is_sti);
#if defined(USE_IAUTH)
	report_iauth_stats(cptr, name);
#endif
}

aMotd		*rmotd = NULL;

void read_rmotd(filename)
char *filename;
{
	FILE *fd;
	register aMotd *temp, *last;
	char line[80];
	register char *tmp;
	
	if ((fd = fopen(filename, "r")) == NULL)
		return;
	for(;rmotd != NULL;rmotd=last)
	    {
		last = rmotd->next;
		MyFree(rmotd->line);
		MyFree(rmotd);
	    }

	last = NULL;

	while (NULL != (fgets(line, sizeof(line), fd)))
	    {
		if ((tmp = strchr(line, '\r')) != NULL)
			*tmp = (char) 0;
		else if ((tmp = strchr(line, '\n')) != NULL)
			*tmp = (char) 0;

		temp = (aMotd *)MyMalloc(sizeof(aMotd));
		if (!temp)
			outofmemory();
		temp->line = mystrdup(line);
		temp->next = NULL;
		       if (!rmotd)
			rmotd = temp;
		else
			last->next = temp;
		last = temp;
	    }
	fclose(fd);
}     

aMotd		*motd = NULL;
time_t		motd_mtime;

void read_motd(filename)
char *filename;
{
	FILE *f;
	int fd;
	register aMotd *temp, *last;
	struct stat Sb;
	char line[80];
	register char *tmp;
#ifndef USE_OLD8BIT
	conversion_t *conv;
	char line2[512];
	char *rline;
	size_t len;
#endif

	if ((fd = open(filename, O_RDONLY)) == -1)
		return;
	if (fstat(fd, &Sb) == -1)
	    {
		close(fd);
		return;
	    }
	if (Sb.st_mtime <= motd_mtime)
	{
		close(fd);
		return;
	}

	f = fdopen(fd, "r");
	if (f == NULL)
	{
		close(fd);
		return;
	}
	motd_mtime = Sb.st_mtime;
	for(;motd != NULL;motd=last)
	    {
		last = motd->next;
		MyFree(motd->line);
		MyFree(motd);
	    }

	last = NULL;
#ifndef USE_OLD8BIT
	conv = conv_get_conversion(config_charset);
#endif
	while (NULL != (fgets(line, sizeof(line), f)))
	    {
		if ((tmp = strchr(line, '\r')) != NULL)
			*tmp = (char) 0;
		else if ((tmp = strchr(line, '\n')) != NULL)
			*tmp = (char) 0;

#ifndef USE_OLD8BIT
		rline = line2;
		len = conv_do_in(conv, line, strlen(line), &rline, sizeof(line2));
		rline[len] = 0;
#endif
		temp = (aMotd *)MyMalloc(sizeof(aMotd));
		if (!temp)
			outofmemory();
#ifndef USE_OLD8BIT
		temp->line = mystrdup(rline);
#else
		temp->line = mystrdup(line);
#endif
		temp->next = NULL;
		if (!motd)
			motd = temp;
		else
			last->next = temp;
		last = temp;
	    }
	close(fd);
#ifndef USE_OLD8BIT
	conv_free_conversion(conv);
#endif
}     

#ifndef USE_OLD8BIT
void set_internal_encoding(aClient *cptr, aConfItem *aconf)
{
    conversion_t *old = NULL, *conv;
#ifdef IRCD_CHANGE_LOCALE
    char localename[24];

#endif
    /* set new charset at first */
    if (!aconf || !aconf->passwd || !*aconf->passwd ||
	!(conv = conv_set_internal(&old, aconf->passwd)))
	    conv = conv_set_internal(&old, CHARSET_UNICODE); /* it's default */
    if (cptr)
	cptr->conv = conv;
    /* now we know what charset to use so update locale and Force8bit */
#ifdef IRCD_CHANGE_LOCALE
    snprintf(localename, sizeof(localename), LOCALE ".%s",
	     conv_charset(conv));
    if (setlocale(LC_ALL, localename) == NULL)
    {
	setlocale(LC_ALL, LOCALE "." CHARSET_8BIT);
	setlocale(LC_TIME, "C");
	if (strcasecmp (conv_charset(conv), CHARSET_8BIT))
	    Force8bit = 1;
    }
#else
    if (strcasecmp (conv_charset(conv), CHARSET_8BIT))
	Force8bit = 1;
#endif
    /* if internal charset is unicode then set default link to unicode too */
    if (!strcasecmp (conv_charset(conv), CHARSET_UNICODE))
	UseUnicode = 1;
    else
	UseUnicode = 0;
    /* let's recode all if internal charset was changed */
    if (old)
    {
	aClient *acptr;
	static char buff[MB_LEN_MAX*BUFSIZE+1]; /* must be long enough for any field */

	/* transcode all clients */
	for (acptr = client; acptr; acptr = acptr->next)
	{
	    del_from_client_hash_table(acptr);
	    conv_transcode(old, acptr->name, buff);
	    add_to_client_hash_table(acptr->name, acptr);
	    if (acptr->info != DefInfo) /* it might be constant! */
		conv_transcode_realloc(old, acptr->info, buff);
	    if (IsServer(acptr))
		conv_transcode(old, acptr->serv->by, buff);
	}
	transcode_channels(old);
	transcode_history(old);
	transcode_collmaps(old);
    }
}
#endif
