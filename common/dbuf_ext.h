/************************************************************************
 *   IRC - Internet Relay Chat, common/dbuf_ext.h
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

/*  This file contains external definitions for global variables and functions
    defined in common/dbuf.c.
 */

/*  External definitions for global variables.
 */
#ifndef DBUF_C
#ifdef	CLIENT_COMPILE
extern u_int dbufalloc;
#endif
extern u_int poolsize;
extern dbufbuf *freelist;
#endif /* DBUF_C */

/*  External definitions for global functions.
 */
#ifndef DBUF_C
#define EXTERN extern
#else /* DBUF_C */
#define EXTERN
#endif /* DBUF_C */
EXTERN void dbuf_init();
EXTERN int dbuf_malloc_error(dbuf *dyn);
EXTERN long dbuf_put(dbuf *dyn, char *buf, long length);
EXTERN char *dbuf_map(dbuf *dyn, long *length);
EXTERN long dbuf_delete(dbuf *dyn, long length);
EXTERN long dbuf_get(dbuf *dyn, char *buf, long length);
/*
EXTERN long dbuf_copy(dbuf *dyn, register char *buf, long length);
*/
EXTERN long dbuf_getmsg(dbuf *dyn, char *buf, register long length);
#undef EXTERN
