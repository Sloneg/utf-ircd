/************************************************************************
 *   IRC - Internet Relay Chat, common/parse_ext.h
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
 */

/*  External definitions for global variables.
 */
#ifndef PARSE_C
#ifdef	CLIENT_COMPILE
extern char userhost[];
#endif /* CLIENT_COMPILE */
extern struct Message msgtab[];
#endif /* PARSE_C */

/*  External definitions for global functions.
 */
#ifndef PARSE_C
#define EXTERN extern
#else /* PARSE_C */
#define EXTERN
#endif /* PARSE_C */
#ifndef CLIENT_COMPILE
EXTERN aClient *find_client(char *name, Reg aClient *cptr);
EXTERN aClient *find_service(char *name, Reg aClient *cptr);
EXTERN aClient *find_server(char *name, Reg aClient *cptr);
EXTERN aClient *find_mask(char *name, aClient *cptr);
EXTERN aServer *find_tokserver(int token, aClient *cptr, aClient *c2ptr);
EXTERN aClient *find_name(char *name, aClient *cptr);
#else /* CLIENT_COMPILE */
EXTERN aClient *find_client(char *name, aClient *cptr);
EXTERN aClient *find_server(char *name, aClient *cptr);
#endif /* CLIENT_COMPILE */
EXTERN aClient *find_userhost(char *user, char *host, aClient *cptr,
				   int *count);
EXTERN aClient *find_person(char *name, aClient *cptr);
EXTERN int parse(aClient *cptr, char *buffer, char *bufend);
EXTERN char *getfield(char *irc_newline);
#undef EXTERN
