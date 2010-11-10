/************************************************************************
 *   IRC - Internet Relay Chat, ircd/s_misc_ext.h
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
 *   $Id: s_misc_ext.h,v 1.9 2010-11-10 13:38:39 gvs Exp $
 */

/*  This file contains external definitions for global variables and functions
    defined in ircd/s_misc.c.
 */

/*  External definitions for global variables.
 */
#ifndef S_MISC_C
extern struct stats ircst, *ircstp;
extern aMotd *motd;
extern time_t motd_mtime;
#ifdef RUSNET_RLINES
extern aMotd *rmotd;
#endif
#endif /* S_MISC_C */

/*  External definitions for global functions.
 */
#ifndef S_MISC_C
#define EXTERN extern
#else /* S_MISC_C */
#define EXTERN
#endif /* S_MISC_C */
EXTERN char *date (time_t clock);
EXTERN int check_registered_user (aClient *sptr);
EXTERN int check_registered (aClient *sptr);
EXTERN int check_registered_service (aClient *sptr);
#ifdef RUSNET_IRCD
EXTERN char *get_client_xname (aClient *sptr, int isop);
#endif
EXTERN char *get_client_name (aClient *sptr, int showip);
EXTERN char *get_client_host (aClient *cptr);
EXTERN void get_sockhost (Reg aClient *cptr, Reg char *host);
EXTERN char *my_name_for_link (char *name, Reg int count);
EXTERN int mark_blind_servers (aClient *cptr, char *name);
EXTERN int exit_client (aClient *cptr, aClient *sptr, aClient *from,
			    char *comment);
EXTERN void checklist(void);
EXTERN void initstats(void);
EXTERN void tstats (aClient *cptr, char *name);
EXTERN void read_motd (char *filename);
#ifdef RUSNET_RLINES
EXTERN void read_rmotd (char *filename);
#endif
#if defined(RUSNET_IRCD) && !defined(USE_OLD8BIT)
EXTERN void set_internal_encoding (aClient *cptr, aConfItem *aconf);
#endif
#undef EXTERN
