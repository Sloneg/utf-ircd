/************************************************************************
 *   IRC - Internet Relay Chat, ircd/s_err.c
 *   Copyright (C) 1992 Darren Reed
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
#define S_ERR_C
#include "s_externs.h"
#undef S_ERR_C

typedef	struct	{
	int	num_val;
	char	*num_form;
} Numeric;

static	char	*prepbuf(char *, char *, char *, int, char *);
static	char	numbuff[512];

static	Numeric	local_replies[] = {
/* 000 */	{ 0, (char *)NULL },
/* 001 */	{ RPL_WELCOME, ":Welcome to the Internet Relay Network %s" },
#ifdef USE_SSL
/* 002 */	{ RPL_YOURHOST, ":Your host is %s, running version %s with SSL support" },
#else
/* 002 */	{ RPL_YOURHOST, ":Your host is %s, running version %s" },
#endif
/* 003 */	{ RPL_CREATED, ":This server was created %s" },
# ifdef USE_SSL
/* 004 */	{ RPL_MYINFO, "%s %s abcoOiIrswx abcehiIklmnoOpqrRstvz" },
# else
/* 004 */	{ RPL_MYINFO, "%s %s abcoOiIrwx abcehiIklmnoOpqrRstvz" },
# endif
#ifndef SEND_ISUPPORT
/* 005 */	{ RPL_BOUNCE, ":Try server %s, port %d" },
#else
/* 005 */      	{ RPL_ISUPPORT, "%s :are supported by this server" },
#endif
/* 006 */      	{ 0, (char *)NULL },
/* 007 */      	{ 0, (char *)NULL },
/* 008 */      	{ 0, (char *)NULL },
/* 009 */      	{ 0, (char *)NULL },
#ifdef SEND_ISUPPORT
/* 010 */      	{ RPL_BOUNCE, "%s %d :Please use this Server/Port instead" },
#else
/* 010 */      	{ 0, (char *)NULL },
#endif
/* 011 */      	{ 0, (char *)NULL },
/* 012 */      	{ 0, (char *)NULL },
/* 013 */      	{ 0, (char *)NULL },
/* 014 */      	{ 0, (char *)NULL },
/* 015 */      	{ 0, (char *)NULL },
/* 016 */      	{ 0, (char *)NULL },
/* 017 */      	{ 0, (char *)NULL },
/* 018 */      	{ 0, (char *)NULL },
/* 019 */      	{ 0, (char *)NULL },
/* 020 */      	{ RPL_HELLO, ":*** %s" },
		{ 0, (char *)NULL }
};

static	Numeric	numeric_errors[] = {
/* 401 */	{ ERR_NOSUCHNICK, "%s :No such nick/channel" },
/* 402 */	{ ERR_NOSUCHSERVER, "%s :No such server" },
/* 403 */	{ ERR_NOSUCHCHANNEL, "%s :No such channel" },
/* 404 */	{ ERR_CANNOTSENDTOCHAN, "%s :Cannot send to channel" },
/* 405 */	{ ERR_TOOMANYCHANNELS, "%s :You have joined too many channels" },
/* 406 */	{ ERR_WASNOSUCHNICK, "%s :There was no such nickname" },
/* 407 */	{ ERR_TOOMANYTARGETS,
		"%s :%s recipients. %s" },
/* 408 */	{ ERR_NOSUCHSERVICE, "%s :No such service" },
/* 409 */	{ ERR_NOORIGIN, ":No origin specified" },
		{ 0, (char *)NULL },
/* 411 */	{ ERR_NORECIPIENT, ":No recipient given (%s)" },
/* 412 */	{ ERR_NOTEXTTOSEND, ":No text to send" },
/* 413 */	{ ERR_NOTOPLEVEL, "%s :No toplevel domain specified" },
/* 414 */	{ ERR_WILDTOPLEVEL, "%s :Wildcard in toplevel Domain" },
/* 415 */	{ ERR_BADMASK, "%s :Bad Server/host mask" },
/* 416 */	{ ERR_TOOMANYMATCHES, "%s :Output too long (try locally)" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 421 */	{ ERR_UNKNOWNCOMMAND, "%s :Unknown command" },
/* 422 */	{ ERR_NOMOTD, ":MOTD File is missing" },
/* 423 */	{ ERR_NOADMININFO,
			"%s :No administrative info available" },
/* 424 */	{ ERR_FILEERROR, ":File error doing %s on %s" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 431 */	{ ERR_NONICKNAMEGIVEN, ":No nickname given" },
/* 432 */	{ ERR_ERRONEOUSNICKNAME, "%s :Erroneous Nickname" },
/* 433 */	{ ERR_NICKNAMEINUSE, "%s :Nickname is already in use." },
/* 434 */	{ ERR_SERVICENAMEINUSE, (char *)NULL },
/* 435 */	{ ERR_SERVICECONFUSED, (char *)NULL },
/* 436 */	{ ERR_NICKCOLLISION, "%s :Nickname collision KILL from %s@%s" },
/* 437 */	{ ERR_UNAVAILRESOURCE,
			"%s :Nick/channel is temporarily unavailable" },
#ifdef HOLD_ENFORCED_NICKS
/* 438 */	{ ERR_NICKTOOFAST, ":Wait a minute before changing nickname" },
#else
		{ 0, (char *)NULL },
#endif
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ ERR_USERNOTINCHANNEL, "%s %s :They aren't on that channel" },
		{ ERR_NOTONCHANNEL, "%s :You're not on that channel" },
/* 443 */	{ ERR_USERONCHANNEL, "%s %s :is already on channel" },
/* 444 */	{ ERR_NOLOGIN, "%s :User not logged in" },
#ifndef	ENABLE_SUMMON
/* 445 */	{ ERR_SUMMONDISABLED, ":SUMMON has been disabled" },
#else
		{ 0, (char *)NULL },
#endif
#ifndef	ENABLE_USERS
/* 446 */	{ ERR_USERSDISABLED, ":USERS has been disabled" },
#else
		{ 0, (char *)NULL },
#endif
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 450 */	{ ERR_NOSPAM, ":Spam is not allowed" },
/* 451 */	{ ERR_NOTREGISTERED, ":You have not registered" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 461 */	{ ERR_NEEDMOREPARAMS, "%s :Not enough parameters" },
/* 462 */	{ ERR_ALREADYREGISTRED,
			":Unauthorized command (already registered)" },
/* 463 */	{ ERR_NOPERMFORHOST, ":Your host isn't among the privileged" },
/* 464 */	{ ERR_PASSWDMISMATCH, ":Password Incorrect" },
/* 465 */	{ ERR_YOUREBANNEDCREEP, ":You are banned from this server" },
/* 466 */	{ ERR_YOUWILLBEBANNED, (char *)NULL },
/* 467 */	{ ERR_KEYSET, "%s :Channel key already set" },
/* 468 */	{ ERR_NOCODEPAGE, "%s :Invalid charset" },
/* 469 */	{ ERR_UNRECOGNIZED,
			"%s :Only registered nicknames allowed (+R)"},
/* 470 */	{ ERR_7BIT, "%s :Only latin-coded nicknames allowed (+z)" },
/* 471 */	{ ERR_CHANNELISFULL, "%s :Cannot join channel (+l)" },
/* 472 */	{ ERR_UNKNOWNMODE  , "%c :is unknown mode char to me for %s" },
/* 473 */	{ ERR_INVITEONLYCHAN, "%s :Cannot join channel (+i)" },
/* 474 */	{ ERR_BANNEDFROMCHAN, "%s :Cannot join channel (+b)" },
/* 475 */	{ ERR_BADCHANNELKEY, "%s :Cannot join channel (+k)" },
/* 476 */	{ ERR_BADCHANMASK, "%s :Bad Channel Mask" },
/* 477 */	{ ERR_NOCHANMODES, "%s :Channel doesn't support modes" },
/* 478 */	{ ERR_BANLISTFULL, "%s %s :Channel list is full" },
/* 479 */	{ ERR_NOCOLOR, "%s :Does not accept colors (+c)" },
#ifdef WALLOPS_TO_CHANNEL
/* 480 */	{ ERR_NOWALLOP,
		":Join &WALLOPS instead" },
#else
		{ 0, (char *)NULL },
#endif
/* 481 */	{ ERR_NOPRIVILEGES,
			":Permission Denied- You're not an IRC operator" },
/* 482 */	{ ERR_CHANOPRIVSNEEDED, "%s :You're not channel operator" },
/* 483 */	{ ERR_CANTKILLSERVER, "%s :You can't kill a server!" },
/* 484 */	{ ERR_RESTRICTED, ":Your connection is restricted!" },
/* 485 */	{ ERR_UNIQOPRIVSNEEDED,
			  ":You're not the original channel operator" },
/* 486 */	{ ERR_RLINED, ":Your connection is Restricted" },
/* 487 */	{ ERR_REGONLY,
			":%s accepts messages from registered nicks only" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 491 */	{ ERR_NOOPERHOST, ":No O-lines for your host" },
/* 492 */	{ ERR_NOSERVICEHOST, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 500 */	{ ERR_NOREHASHPARAM, "%s :Unknown REHASH parameter" },
/* 501 */	{ ERR_UMODEUNKNOWNFLAG, ":Unknown MODE flag" },
/* 502 */	{ ERR_USERSDONTMATCH, ":Can't change mode for other users" },
		{ 0, (char *)NULL }
};

static	Numeric	numeric_replies[] = {
/* 300 */	{ RPL_NONE, (char *)NULL },
/* 301 */	{ RPL_AWAY, "%s :%s" },
/* 302 */	{ RPL_USERHOST, ":" },
/* 303 */	{ RPL_ISON, ":" },
/* 304 */	{ RPL_TEXT, (char *)NULL },
/* 305 */	{ RPL_UNAWAY, ":You are no longer marked as being away" },
/* 306 */	{ RPL_NOWAWAY, ":You have been marked as being away" },
/* 307 */	{ RPL_IDENTIFIED, "%s :Identified by NickServ" },
/* 308 */	{ RPL_NOCOLOR, "%s :Does not accept colors" },
		{ 0, (char *)NULL },	/* is a services admin */
		{ 0, (char *)NULL },	/* is an IRC helper */
/* 311 */	{ RPL_WHOISUSER, "%s %s %s * :%s" },
/* 312 */	{ RPL_WHOISSERVER, "%s %s :%s" },
/* 313 */	{ RPL_WHOISOPERATOR, "%s :is an IRC Operator" },
/* 314 */	{ RPL_WHOWASUSER, "%s %s %s * :%s" },
/* 315 */	{ RPL_ENDOFWHO, "%s :End of WHO list." },
/* 316 */	{ RPL_WHOISCHANOP, (char *)NULL },
/* 317 */	{ RPL_WHOISIDLE, "%s %ld %ld :seconds idle, signon time" },
/* 318 */	{ RPL_ENDOFWHOIS, "%s :End of WHOIS list." },
/* 319 */	{ RPL_WHOISCHANNELS, "%s :%s" },
		{ 0, (char *)NULL },
/* 321 */	{ RPL_LISTSTART, "Channel :Users  Name" },
/* 322 */	{ RPL_LIST, "%s %d :%s" },
/* 323 */	{ RPL_LISTEND, ":End of LIST" },
/* 324 */	{ RPL_CHANNELMODEIS, "%s %s %s" },
/* 325 */	{ RPL_UNIQOPIS, "%s %s" },
		{ 0, (char *)NULL },
/* 327 */	{ RPL_WHOISHOST, "%s :Real host is %s" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 331 */	{ RPL_NOTOPIC, "%s :No topic is set." },
/* 332 */	{ RPL_TOPIC, "%s :%s" },
#ifdef TOPICWHOTIME
/* 333 */       { RPL_TOPICWHOTIME, "%s %s %lu" },
#else
		{ 0, (char *)NULL },
#endif
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 341 */	{ RPL_INVITING, "%s %s" },
/* 342 */	{ RPL_SUMMONING, "%s :User summoned to irc" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 346 */	{ RPL_INVITELIST, "%s %s" },
/* 347 */       { RPL_ENDOFINVITELIST, "%s :End of Channel Invite List" },
/* 348 */	{ RPL_EXCEPTLIST, "%s %s" },
/* 349 */       { RPL_ENDOFEXCEPTLIST, "%s :End of Channel Exception List" },
		{ 0, (char *)NULL },
/* 351 */	{ RPL_VERSION, "%s%s %s :%s" },
/* 352 */	{ RPL_WHOREPLY, "%s %s %s %s %s %s :%d %s" },
/* 353 */	{ RPL_NAMREPLY, "%s" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 361 */	{ RPL_KILLDONE, (char *)NULL },
/* 362 */	{ RPL_CLOSING, "%s :Closed. Status = %d" },
/* 363 */	{ RPL_CLOSEEND, "%d: Connections Closed" },
/* 364 */	{ RPL_LINKS, "%s %s :%d %s" },
/* 365 */	{ RPL_ENDOFLINKS, "%s :End of LINKS list." },
/* 366 */	{ RPL_ENDOFNAMES, "%s :End of NAMES list." },
/* 367 */	{ RPL_BANLIST, "%s %s" },
/* 368 */	{ RPL_ENDOFBANLIST, "%s :End of Channel Ban List" },
/* 369 */	{ RPL_ENDOFWHOWAS, "%s :End of WHOWAS" },
		{ 0, (char *)NULL },
/* 371 */	{ RPL_INFO, ":%s" },
/* 372 */	{ RPL_MOTD, ":- %s" },
/* 373 */	{ RPL_INFOSTART, ":Server INFO" },
/* 374 */	{ RPL_ENDOFINFO, ":End of INFO list." },
/* 375 */	{ RPL_MOTDSTART, ":- %s Message of the Day - " },
/* 376 */	{ RPL_ENDOFMOTD, ":End of MOTD command." },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 381 */	{ RPL_YOUREOPER, ":You are now an IRC supermouse" },
/* 382 */	{ RPL_REHASHING, "%s :Rehashing [%s]" },
/* 383 */	{ RPL_YOURESERVICE, ":You are service %s" },
/* 384 */	{ RPL_MYPORTIS, "%d :Port to local server is\r\n" },
/* 385 */	{ RPL_NOTOPERANYMORE, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 391 */	{ RPL_TIME, "%s :%s" },
#ifdef	ENABLE_USERS
/* 392 */	{ RPL_USERSSTART, ":UserID   Terminal  Host" },
/* 393 */	{ RPL_USERS, ":%-8s %-9s %-8s" },
/* 394 */	{ RPL_ENDOFUSERS, ":End of Users" },
/* 395 */	{ RPL_NOUSERS, ":Nobody logged in." },
#else
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
#endif
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 200 */	{ RPL_TRACELINK, "Link %s%s %s %s V%X%s %d %d %d" },
/* 201 */	{ RPL_TRACECONNECTING, "Try. %d %s" },
/* 202 */	{ RPL_TRACEHANDSHAKE, "H.S. %d %s" },
/* 203 */	{ RPL_TRACEUNKNOWN, "???? %d %s" },
/* 204 */	{ RPL_TRACEOPERATOR, "Oper %d %s" },
/* 205 */	{ RPL_TRACEUSER, "User %d %s" },
/* 206 */	{ RPL_TRACESERVER, "Serv %d %dS %dC %s %s!%s@%s V%X%s" },
/* 207 */	{ RPL_TRACESERVICE, "Service %d %s 0x%X 0x%X" },
/* 208 */	{ RPL_TRACENEWTYPE, "<newtype> 0 %s" },
/* 209 */	{ RPL_TRACECLASS, "Class %d %d" },
/* 210 */	{ RPL_TRACERECONNECT, "Retry. %d %s" },
/* 211 */	{ RPL_STATSLINKINFO, (char *)NULL },
/* 212 */	{ RPL_STATSCOMMANDS, "%s %u %u %u" },
/* 213 */	{ RPL_STATSCLINE, "%c %s %s %s %d %d %d" },
/* 214 */	{ RPL_STATSNLINE, "%c %s %s %s %d %d %d" },
/* 215 */	{ RPL_STATSILINE, "%c %s %s %s %d %d %d" },
/* 216 */	{ RPL_STATSKLINE, "%c %s!%s %s %d %s" },
/* 217 */	{ RPL_STATSQLINE, "%c %s %s %s %d %d" },
/* 218 */	{ RPL_STATSYLINE, "%c %d %d %d %d %ld %d.%d %d.%d" },
/* 219 */	{ RPL_ENDOFSTATS, "%c :End of STATS report" },
		{ 0, (char *)NULL },
/* 221 */	{ RPL_UMODEIS, "%s" },
/* 222 */	{ RPL_CODEPAGE, "%s :is your charset now" },
/* 223 */	{ RPL_CHARSET, "%s :charset is %s" },
/* 224 */	{ RPL_STATSFLINE, "%c %s %s %s %d %d" },
/* 225 */	{ RPL_WHOISRMODE, "%s :is Restricted" },
/* 226 */	{ RPL_STATSRLINE, "%c %s!%s %s %d %s" },
		{ 0, (char *)NULL },
/* 228 */	{ RPL_STATSTRIGGER, "%c %s %d %s %s" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 231 */	{ RPL_SERVICEINFO, (char *)NULL },
/* 232 */	{ RPL_ENDOFSERVICES, (char *)NULL },
/* 233 */	{ RPL_SERVICE, (char *)NULL },
/* 234 */	{ RPL_SERVLIST, "%s %s %s 0x%X %d :%s" },
/* 235 */	{ RPL_SERVLISTEND, "%s %d :End of service listing" },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
		{ 0, (char *)NULL },
/* 240 */	{ RPL_STATSVLINE, "%c %s %s %s %d %d" },
/* 241 */	{ RPL_STATSLLINE, "%c %s is logged to %s" },
/* 242 */	{ RPL_STATSUPTIME, ":Server Up %d days, %d:%02d:%02d" },
/* 243 */	{ RPL_STATSOLINE, "%c %s %s %s %d %d" },
/* 244 */	{ RPL_STATSHLINE, "%c %s %s %s %d %d" }, 
/* 245 */	{ RPL_STATSSLINE, "%c %s %s %s 0x%X %d" }, 
/* 246 */	{ RPL_STATSPING, "%s %d %d %d %d" },
/* 247 */	{ RPL_STATSBLINE, "%c %s %s %s %d %d" },
		{ 0, (char *)NULL }, /* RPL_STATSDEFINE */
		{ 0, (char *)NULL }, /* RPL_STATSDEBUG */
/* 250 */	{ RPL_STATSDLINE, "%c %s %s %s %d %d" },
/* 251 */	{ RPL_LUSERCLIENT,
		":There are %d users and %d services on %d servers" },
/* 252 */	{ RPL_LUSEROP, "%d :operators online" },
/* 253 */	{ RPL_LUSERUNKNOWN, "%d :unknown connections" },
/* 254 */	{ RPL_LUSERCHANNELS, "%d :channels formed" },
/* 255 */	{ RPL_LUSERME, ":I have %d users, %d services and %d servers" },
/* 256 */	{ RPL_ADMINME, ":Administrative info about %s" },
/* 257 */	{ RPL_ADMINLOC1, ":%s" },
/* 258 */	{ RPL_ADMINLOC2, ":%s" },
/* 259 */	{ RPL_ADMINEMAIL, ":%s" },
		{ 0, (char *)NULL },
/* 261 */	{ 0, (char *)NULL },
/* 262 */	{ RPL_TRACEEND, "%s %s.%s :End of TRACE" },
/* 263 */	{ RPL_TRYAGAIN, "%s :Please wait a while and try again." },
#ifdef USE_SSL
/* 264 */	{ RPL_USINGSSL, "%s :is using encrypted connection" },
#else
		{ 0, (char *)NULL },
#endif
#ifdef EXTRA_STATISTICS
/* 265 */      { RPL_LOCALUSERS, ":Current local users: %d  Max: %d" },
/* 266 */      { RPL_GLOBALUSERS, ":Current global users: %d  Max: %d" },
#endif
		{ 0, (char *)NULL }
};

char	*err_str(numeric, to)
int	numeric;
char	*to;
{
	Reg	Numeric	*nptr;
	Reg	int	num = numeric;

	if (BadPtr(to))		/* for unregistered clients */
		to = "*";

	num -= numeric_errors[0].num_val;
	if (num < 0 || num > ERR_USERSDONTMATCH)
		sprintf(numbuff,
			":%s %d %s :INTERNAL ERROR: BAD NUMERIC! %d",
			ME, numeric, to, num);
	else
	    {
		nptr = &numeric_errors[num];
		Debug((DEBUG_NUM,
			"err_str: to %s #%d num %d nptr %#x %d [%s]", to,
			numeric, num, nptr, nptr->num_val, nptr->num_form));
		if (!nptr->num_form || !nptr->num_val)
			sprintf(numbuff,
				":%s %d %s :NO ERROR FOR NUMERIC ERROR %d",
				ME, numeric, to, num);
		else
			(void)prepbuf(numbuff, ME, to, nptr->num_val,
				      nptr->num_form);
	    }
	return numbuff;
}


char	*rpl_str(numeric, to)
int	numeric;
char	*to;
{
	Reg	Numeric	*nptr;
	Reg	int	num = numeric;

	if (num > 100)
		num -= (num > 300) ? 300 : 100;

	if (BadPtr(to))		/* for unregistered clients */
		to = "*";

	if (num < 0 || num > 200)
		sprintf(numbuff,
			":%s %d %s :INTERNAL REPLY ERROR: BAD NUMERIC! %d",
			ME, numeric, to, num);
	else
	    {
		if (numeric > 99)
			nptr = &numeric_replies[num];
		else
			nptr = &local_replies[num];
		Debug((DEBUG_NUM,
			"rpl_str: to %s #%d num %d nptr %#x %d [%s]", to,
			numeric, num, nptr, nptr->num_val, nptr->num_form));
		if (!nptr->num_form || !nptr->num_val)
			sprintf(numbuff,
				":%s %d %s :NO REPLY FOR NUMERIC ERROR %d",
				ME, numeric, to, num);
		else
			(void)prepbuf(numbuff, ME, to, nptr->num_val,
				      nptr->num_form);
	    }
	return numbuff;
}

static	char	*prepbuf(buffer, from, to, num, tail)
char	*buffer;
Reg	int	num;
char	*from, *to, *tail;
{
	Reg	char	*s = buffer;

	*s++ = ':';
	(void)strcpy(s, from);
	(void)strcat(s, " ");
	s += strlen(s);

	*s++ = '0' + num/100;
	num %= 100;
	*s++ = '0' + num/10;
	*s++ = '0' + num%10;
	*s++ = ' ';
	(void)strcpy(s, to);
	s += strlen(s);
	*s++ = ' ';
	(void)strcpy(s, tail);
	return buffer;
}
