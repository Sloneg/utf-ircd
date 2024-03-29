/************************************************************************
 *   IRC - Internet Relay Chat, common/match_ext.h
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
    defined in common/match.c.
 */

/*  External definitions for global variables.
 */
#ifndef MATCH_C
extern char tolowertab[];
extern char touppertab[];
extern char char_atribs[];
extern int  CharAttrs[];
#if defined(USE_OLD8BIT) || defined(LOCALE_STRICT_NAMES)
extern char validtab[];
#endif

/*  External definitions for global functions.
 */
#define EXTERN extern
#else /* MATCH_C */
#define EXTERN
#endif /* MATCH_C */
EXTERN int match (char *mask, char *name);
EXTERN char *collapse (char *pattern);
EXTERN int mycmp (const char *s1, const char *s2);
EXTERN int myncmp (const char *str1, const char *str2, int n);
#if defined(USE_OLD8BIT) || defined(LOCALE_STRICT_NAMES)
EXTERN void setup_validtab (void);
#endif
#undef EXTERN


