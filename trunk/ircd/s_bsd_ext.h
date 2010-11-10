/************************************************************************
 *   IRC - Internet Relay Chat, ircd/s_bsd_ext.h
 *   Copyright (C) 1997 Alain Nissen
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
 *   $Id: s_bsd_ext.h,v 1.9 2010-11-10 13:38:39 gvs Exp $
 */

/*  This file contains external definitions for global variables and functions
    defined in ircd/s_bsd.c.
 */

/*  External definitions for global variables.
 */
#ifndef S_BSD_C
extern aClient *local[];
extern FdAry fdas, fdaa, fdall;
extern int highest_fd, readcalls, udpfd, resfd, adfd, isfd;
extern time_t timeofday;
#endif /* S_BSD_C */

/*  External definitions for global functions.
 */
#ifndef S_BSD_C
#define EXTERN extern
#else /* S_BSD_C */
#define EXTERN
#endif /* S_BSD_C */
EXTERN void add_local_domain (char *hname, int size);
EXTERN void report_error (char *text, aClient *cptr);
EXTERN int inetport (aClient *cptr, char *ip, char *ipmask, int port,
		int dolisten);
EXTERN int add_listener (aConfItem *aconf);
EXTERN void close_listeners();
EXTERN void open_listener(aClient *cptr);
EXTERN void reopen_listeners(void);
EXTERN void start_iauth (int);
EXTERN void init_sys();
EXTERN void daemonize(void);
EXTERN void write_pidfile();
EXTERN int check_client (Reg aClient *cptr);
EXTERN int check_server_init (aClient *cptr);
EXTERN int check_server (aClient *cptr, Reg struct hostent *hp,
			     Reg aConfItem *c_conf, Reg aConfItem *n_conf);
EXTERN void close_connection (aClient *cptr);
EXTERN void close_client_fd(aClient *cptr);
EXTERN int get_sockerr (aClient *cptr);
EXTERN void set_non_blocking (int fd, aClient *cptr);
EXTERN aClient *add_connection (aClient *cptr, int fd);
EXTERN int read_message (time_t delay, FdAry *fdp, int ro);
EXTERN int connect_server (aConfItem *aconf, aClient *by,
			       struct hostent *hp);
EXTERN void get_my_name (aClient *cptr, char *name, int len);
EXTERN int setup_ping (aConfItem *aconf);
EXTERN void send_ping (aConfItem *aconf);
#if defined(ENABLE_SUMMON) || defined(ENABLE_USERS)
EXTERN int utmp_open();
EXTERN int utmp_read (int fd, char *name, char *line, char *host,
			  int hlen);
EXTERN int utmp_close(int fd);
#ifdef  ENABLE_SUMMON
EXTERN void summon (aClient *who, char *namebuf, char *linebuf,
			char *chname);
#endif /* ENABLE_SUMMON */
#endif /* ENABLE_SUMMON || ENABLE_USERS */
#ifdef	UNIXPORT
EXTERN int unixport (aClient *cptr, char *path, int port);
#endif
#ifdef DELAY_CLOSE
EXTERN time_t delay_close (int);
#endif
#if defined(RUSNET_IRCD) && !defined(USE_OLD8BIT)
EXTERN aClient *find_listener (int port);
#endif
#undef EXTERN

#ifdef DELAY_CLOSE
#ifndef SHUT_RD
# error SHUT_RD not defined! Report buggy OS to ircd-bugs@irc.org
/* Check shutdown(3) manpage for proper definition. */
# define SHUT_RD 0
#endif
#endif
