#************************************************************************
#*   IRC - Internet Relay Chat, Makefile
#*   Copyright (C) 1990, Jarkko Oikarinen
#*
#*   This program is free software; you can redistribute it and/or modify
#*   it under the terms of the GNU General Public License as published by
#*   the Free Software Foundation; either version 1, or (at your option)
#*   any later version.
#*
#*   This program is distributed in the hope that it will be useful,
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#*   GNU General Public License for more details.
#*
#*   You should have received a copy of the GNU General Public License
#*   along with this program; if not, write to the Free Software
#*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#*
#*   $Id: Makefile,v 1.4.2.1 2003/09/30 14:23:20 chourf Exp $
#*
#*/

MANDIR=/usr/local/man

all:

sgml: service doc

doc: INSTALL.sgml
	sgml2txt INSTALL.sgml
	sgml2info INSTALL.sgml

service: SERVICE.sgml
	sgml2txt SERVICE.sgml

install: all
	-${INSTALL} -c -m 644 ircd.8 ${MANDIR}/man8
	-${INSTALL} -c -m 644 irc.1 ${MANDIR}/man1

