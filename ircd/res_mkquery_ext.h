/************************************************************************
 *   IRC - Internet Relay Chat, ircd/res_mkquery_ext.h
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
    defined in ircd/res_mkquery.c.
 */

/*  External definitions for global functions.
 */
#ifndef RES_MKQUERY_C
#define EXTERN extern
#else /* RES_MKQUERY_C */
#define EXTERN
#endif /* RES_MKQUERY_C */
EXTERN int ircd_res_mkquery(int op, const char *dname, int class,
				int type, const u_char *data,
				int datalen, u_char *buf, int buflen);
#undef EXTERN
