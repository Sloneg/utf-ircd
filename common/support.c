/************************************************************************
 *   IRC - Internet Relay Chat, common/support.c
 *   Copyright (C) 1990, 1991 Armin Gruner
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
#define SUPPORT_C
#include "s_externs.h"
#undef SUPPORT_C

char	*mystrdup(s)
const char	*s;
{
	/* Portable strdup(), contributed by mrg, thanks!  -roy */

	char	*t;

	t = (char *) MyMalloc(strlen(s) + 1);
	if (t)
		return ((char *)strcpy(t, s));
	return NULL;
}

#if ! defined(HAVE_STRTOKEN)
/*
** 	strtoken.c --  	walk through a string of tokens, using a set
**			of separators
**			argv 9/90
*/

char *strtoken(save, str, fs)
char **save;
char *str, *fs;
{
    char *pos = *save;	/* keep last position across calls */
    Reg char *tmp;

    if (str)
	pos = str;		/* new string scan */

    while (pos && *pos && index(fs, *pos) != NULL)
	pos++; 		 	/* skip leading separators */

    if (!pos || !*pos)
	return (pos = *save = NULL); 	/* string contains only sep's */

    tmp = pos; 			/* now, keep position of the token */

    while (*pos && index(fs, *pos) == NULL)
	pos++; 			/* skip content of the token */

    if (*pos)
	*pos++ = '\0';		/* remove first sep after the token */
    else
	pos = NULL;		/* end of string */

    *save = pos;
    return(tmp);
}
#endif /* HAVE_STRTOKEN */

#if ! defined(HAVE_STRTOK)
/*
** NOT encouraged to use!
*/

char *strtok(str, fs)
char *str, *fs;
{
    static char *pos;

    return strtoken(&pos, str, fs);
}

#endif /* HAVE_STRTOK */

#if ! defined(HAVE_STRERROR)
/*
**	strerror - return an appropriate system error string to a given errno
**
**		   argv 11/90
*/

char *strerror(err_no)
int err_no;
{
	static	char	buff[40];
	char	*errp;

	errp = (err_no > sys_nerr ? (char *)NULL : sys_errlist[err_no]);

	if (errp == (char *)NULL)
	    {
		errp = buff;
		sprintf(errp, "Unknown Error %d", err_no);
	    }
	return errp;
}

#endif /* HAVE_STRERROR */

/**
 ** myctime()
 **   This is like standard ctime()-function, but it zaps away
 **   the newline from the end of that string. Also, it takes
 **   the time value as parameter, instead of pointer to it.
 **   Note that it is necessary to copy the string to alternate
 **   buffer (who knows how ctime() implements it, maybe it statically
 **   has newline there and never 'refreshes' it -- zapping that
 **   might break things in other places...)
 **
 **/

char	*myctime(value)
time_t	value;
{
	static	char	buf[28];
	Reg	char	*p;

	(void)strncpy(buf, ctime(&value), 28);
	buf[27] = '\0';
	if ((p = (char *)index(buf, '\n')) != NULL)
		*p = '\0';

	return buf;
}

/*
** mybasename()
**	removes path from a filename
*/
char *
mybasename(path)
char *path;
{
	char *lastslash;

	if ((lastslash = rindex(path, '/')))
		return(lastslash + 1);
	return path;
}

/*
** Colorless string copy, used to strip ANSI colors as well as bold, italic,
** and underline from a message. Currently only used to check spam because
** of performance penalty it introduces. See man strdup(3) for details
*/
#ifdef STRIP_COLORS
char *cstrip(char *src)
{
	Reg char *s, *d;
	char *dest = MyMalloc(strlen(src) + 1);

	if (!dest)
		return src;

	for (s = src, d = dest; *s; s++)
	{
		/* color code matches (\d{1,2}(,\d{1,2})?)? pattern	*/
		/* several color codes may come in sequence		*/
		while (*s == '\x03')
		{
			s++;
			if (isdigit(*s)) s++;
			if (isdigit(*s)) s++;
			if (*s == ',') s++;
			if (isdigit(*s)) s++;
			if (isdigit(*s)) s++;
		}

		if (*s == '\0') break;	/* deal with malformed codes */
		if (*s == '\x0f' || *s == '\x1f' || *s == '\x02'
				|| *s == '\x12' || *s == '\x16')
			continue;

		*d++ = *s;
	}

	*d = '\0'; /* terminate string */

	return dest;
}
#endif

#ifdef INET6
/*
 * inetntop: return the : notation of a given IPv6 internet number.
 *	     or the dotted-decimal notation for IPv4
 *           make sure the compressed representation (rfc 1884) isn't used.
 */
char *inetntop(af, in, out, the_size)
int af;
const void *in;
char *out;
size_t the_size;
{
	static char local_dummy[MYDUMMY_SIZE];

	if (!inet_ntop(af, in, local_dummy, the_size))
	{
		/* good that every function calling this one
		 * checks the return value ... NOT */
		return NULL;
	}	
	/* quick and dirty hack to give ipv4 just ipv4 instead of
	 * ::ffff:ipv4 - Q */
	if (af == AF_INET6 && IN6_IS_ADDR_V4MAPPED((struct in6_addr *)in))
	{
		char	*p;

		if (!(p = strstr(local_dummy, ":ffff:")) &&
			!(p = strstr(local_dummy, ":FFFF:")))
		{
			return NULL;	/* crash and burn */
		}
		strcpy(out, p + 6);
		return out;
	}
	if (strstr(local_dummy, "::"))
	    {
		char cnt = 0, *cp = local_dummy, *op = out;

		while (*cp)
		    {
			if (*cp == ':')
				cnt += 1;
			if (*cp++ == '.')
			    {
				cnt += 1;
				break;
			    }
		    }
		cp = local_dummy;
		while (*cp)
		    {
			*op++ = *cp++;
			if (*(cp-1) == ':' && *cp == ':')
			    {
				if ((cp-1) == local_dummy)
				    {
					op--;
					*op++ = '0';
					*op++ = ':';
				    }

				*op++ = '0';
				while (cnt++ < 7)
				    {
					*op++ = ':';
					*op++ = '0';
				    }
			    }
		    }
		if (*(op-1)==':') *op++ = '0';
		*op = '\0';
#ifndef	CLIENT_COMPILE
		Debug((DEBUG_DNS,"Expanding `%s' -> `%s'", local_dummy,
		       out));
#endif
	    }
	else
		bcopy(local_dummy, out, 64);
	return out;
}

/* inetpton(af, src, dst)
**
** This is a wrapper for inet_pton(), so we can use ipv4 addresses with an
** af of AF_INET6, and that it gets converted to ipv4 mapped ipv6.
*/
int	inetpton(int af, const char *src, void *dst)
{
	int	i;

	/* an empty string should listen to all */
	if (af == AF_INET6 && *src && !strchr(src, ':'))
	    {
		i = inet_pton(AF_INET, src, dst);

		/* ugly hack */
		memcpy((char *)dst + 12, dst, 4);
		memset(dst, 0, 10);
		memset((char *)dst + 10, 0xff, 2);
		return i;
	    }
	return inet_pton(af, src, dst);
}
#endif

#if ! defined(HAVE_INET_NTOA)
/*
**	inetntoa  --	changed name to remove collision possibility and
**			so behaviour is gaurunteed to take a pointer arg.
**			-avalon 23/11/92
**	inet_ntoa --	returned the dotted notation of a given
**			internet number (some ULTRIX don't have this)
**			argv 11/90).
**	inet_ntoa --	its broken on some Ultrix/Dynix too. -avalon
*/

char	*inetntoa(in)
char	*in;
{
	static	char	buf[16];
	Reg	u_char	*s = (u_char *)in;
	Reg	int	a,b,c,d;

	a = (int)*s++;
	b = (int)*s++;
	c = (int)*s++;
	d = (int)*s;
	(void)sprintf(buf, "%d.%d.%d.%d", a,b,c,d );

	return buf;
}
#endif

#if ! defined(HAVE_INET_NETOF)
/*
**	inet_netof --	return the net portion of an internet number
**			argv 11/90
*/
int inetnetof(in)
struct in_addr in;
{
    register u_long i = ntohl(in.s_addr);
    
    if (IN_CLASSA(i))
	    return (((i)&IN_CLASSA_NET) >> IN_CLASSA_NSHIFT);
    else if (IN_CLASSB(i))
	    return (((i)&IN_CLASSB_NET) >> IN_CLASSB_NSHIFT);
    else
	    return (((i)&IN_CLASSC_NET) >> IN_CLASSC_NSHIFT);
}
#endif

#if ! defined(HAVE_INET_ADDR)
# ifndef INADDR_NONE
#  define INADDR_NONE   0xffffffff
# endif
/*
 * Ascii internet address interpretation routine.
 * The value returned is in network order.
 */
u_long
inetaddr(cp)
	register const char *cp;
{
	struct in_addr val;

	if (inetaton(cp, &val))
		return (val.s_addr);
	return (INADDR_NONE);
}
#endif

#if ! defined(HAVE_INET_ATON)
/* 
 * Check whether "cp" is a valid ascii representation
 * of an Internet address and convert to a binary address.
 * Returns 1 if the address is valid, 0 if not.
 * This replaces inet_addr, the return value from which
 * cannot distinguish between failure and a local broadcast address.
 */
int
inetaton(cp, addr)
	register const char *cp;
	struct in_addr *addr;
{
	register u_long val;
	register int base, n;
	register char c;
	u_int parts[4];
	register u_int *pp = parts;

	c = *cp;
	for (;;) {
		/*
		 * Collect number up to ``.''.
		 * Values are specified as for C:
		 * 0x=hex, 0=octal, isdigit=decimal.
		 */
		if (!isdigit(c))
			return (0);
		val = 0; base = 10;
		if (c == '0') {
			c = *++cp;
			if (c == 'x' || c == 'X')
				base = 16, c = *++cp;
			else
				base = 8;
		}
		for (;;) {
			if (isascii(c) && isdigit(c)) {
				val = (val * base) + (c - '0');
				c = *++cp;
			} else if (base == 16 && isascii(c) && isxdigit(c)) {
				val = (val << 4) |
					(c + 10 - (islower(c) ? 'a' : 'A'));
				c = *++cp;
			} else
				break;
		}
		if (c == '.') {
			/*
			 * Internet format:
			 *	a.b.c.d
			 *	a.b.c	(with c treated as 16 bits)
			 *	a.b	(with b treated as 24 bits)
			 */
			if (pp >= parts + 3)
				return (0);
			*pp++ = val;
			c = *++cp;
		} else
			break;
	}
	/*
	 * Check for trailing characters.
	 */
	if (c != '\0' && (!isascii(c) || !isspace(c)))
		return (0);
	/*
	 * Concoct the address according to
	 * the number of parts specified.
	 */
	n = pp - parts + 1;
	switch (n) {

	case 0:
		return (0);		/* initial nondigit */

	case 1:				/* a -- 32 bits */
		break;

	case 2:				/* a.b -- 8.24 bits */
		if (val > 0xffffff)
			return (0);
		val |= parts[0] << 24;
		break;

	case 3:				/* a.b.c -- 8.8.16 bits */
		if (val > 0xffff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16);
		break;

	case 4:				/* a.b.c.d -- 8.8.8.8 bits */
		if (val > 0xff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
		break;
	}
	if (addr)
		addr->s_addr = htonl(val);
	return (1);
}
#endif

#if defined(DEBUGMODE) && !defined(CLIENT_COMPILE)
void	dumpcore(msg, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)
char	*msg, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9, *p10, *p11;
{
	static	time_t	lastd = 0;
	static	int	dumps = 0;
	char	corename[12];
	time_t	now;
	int	p;

	now = time(NULL);

	if (!lastd)
		lastd = now;
	else if (now - lastd < 60 && dumps > 2)
		(void)s_die(0);
	if (now - lastd > 60)
	    {
		lastd = now;
		dumps = 1;
	    }
	else
		dumps++;
	p = getpid();
	if (fork()>0) {
		kill(p, 3);
		kill(p, 9);
	}
	write_pidfile();
	sprintf(corename, "core.%d", p);
	(void)rename("core", corename);
	Debug((DEBUG_FATAL, "Dumped core : core.%d", p));
	sendto_flag(SCH_ERROR, "Dumped core : core.%d", p);
	Debug((DEBUG_FATAL, msg, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10,p11));
	sendto_flag(SCH_ERROR, msg, p1, p2, p3, p4, p5, p6, p7, p8,p9,p10,p11);
	(void)s_die(0);
}
#endif

#if defined(DEBUGMODE) && !defined(CLIENT_COMPILE) && defined(DO_DEBUG_MALLOC)

static	char	*marray[100000];
static	int	mindex = 0;

#define	SZ_EX	(sizeof(char *) + sizeof(size_t) + 4)
#define	SZ_CHST	(sizeof(char *) + sizeof(size_t))
#define	SZ_CH	(sizeof(char *))
#define	SZ_ST	(sizeof(size_t))

char	*MyMalloc(x)
size_t	x;
{
	register int	i;
	register char	**s;
	char	*ret;

	ret = (char *)malloc(x + (size_t)SZ_EX);

	if (!ret)
	    {
		outofmemory();
	    }
	bzero(ret, (int)x + SZ_EX);
	bcopy((char *)&ret, ret, SZ_CH);
	bcopy((char *)&x, ret + SZ_CH, SZ_ST);
	bcopy("VAVA", ret + SZ_CHST + (int)x, 4);
	Debug((DEBUG_MALLOC, "MyMalloc(%ld) = %#x", x, ret + SZ_CHST));
	for(i = 0, s = marray; *s && i < mindex; i++, s++)
		;
 	if (i < 100000)
	    {
		*s = ret;
		if (i == mindex)
			mindex++;
	    }
	return ret + SZ_CHST;
    }

char    *MyRealloc(x, y)
char	*x;
size_t	y;
    {
	register int	l;
	register char	**s;
	char	*ret, *cp;
	size_t	i;
	int	k;

	if (x != NULL)
	  {
	      x -= SZ_CHST;
	      bcopy(x, (char *)&cp, SZ_CH);
	      bcopy(x + SZ_CH, (char *)&i, SZ_ST);
	      bcopy(x + (int)i + SZ_CHST, (char *)&k, 4);
	      if (bcmp((char *)&k, "VAVA", 4) || (x != cp))
		      dumpcore("MyRealloc %#x %d %d %#x %#x", x, y, i, cp, k);
	  }
	ret = (char *)realloc(x, y + (size_t)SZ_EX);

	if (!ret)
	    {
		outofmemory();
	    }
	bcopy((char *)&ret, ret, SZ_CH);
	bcopy((char *)&y, ret + SZ_CH, SZ_ST);
	bcopy("VAVA", ret + SZ_CHST + (int)y, 4);
	Debug((DEBUG_NOTICE, "MyRealloc(%#x,%ld) = %#x", x, y, ret + SZ_CHST));
	for(l = 0, s = marray; *s != x && l < mindex; l++, s++)
		;
 	if (l < mindex)
		*s = NULL;
	else if (l == mindex)
		Debug((DEBUG_MALLOC, "%#x !found", x));
	for(l = 0, s = marray; *s && l < mindex; l++,s++)
		;
 	if (l < 100000)
	    {
		*s = ret;
		if (l == mindex)
			mindex++;
	    }
	return ret + SZ_CHST;
    }

void	MyFree(void *p)
{
	size_t	i;
	char	*j, *x = p;
	u_char	k[4];
	register int	l;
	register char	**s;

	if (!x)
		return;
	x -= SZ_CHST;

	bcopy(x, (char *)&j, SZ_CH);
	bcopy(x + SZ_CH, (char *)&i, SZ_ST);
	bcopy(x + SZ_CHST + (int)i, (char *)k, 4);

	if (bcmp((char *)k, "VAVA", 4) || (j != x))
		dumpcore("MyFree %#x %ld %#x %#x", x, i, j,
			 (k[3]<<24) | (k[2]<<16) | (k[1]<<8) | k[0]);

	Debug((DEBUG_MALLOC, "MyFree(%#x)",x + SZ_CHST));
#undef	free
	(void)free(x);
#define	free(x)	MyFree(x)

	for (l = 0, s = marray; *s != x && l < mindex; l++, s++)
		;
	if (l < mindex)
		*s = NULL;
	else if (l == mindex)
		Debug((DEBUG_MALLOC, "%#x !found", x));
}
#else
char	*MyMalloc(size_t x)
{
	char *ret = (char *)malloc(x);

	if (!ret)
	    {
# ifndef	CLIENT_COMPILE
		outofmemory();
# else
		perror("malloc");
		exit(-1);
# endif
	    }
	return	ret;
}

char	*MyRealloc(char *x, size_t y)
{
	char *ret = (char *)realloc(x, y);

	if (!ret)
	    {
# ifndef CLIENT_COMPILE
		outofmemory();
# else
		perror("realloc");
		exit(-1);
# endif
	    }
	return ret;
    }
#endif


/*
 * Make 'readable' version string.
 */
char *make_version()
{
	int ve, re, mi;
	int rv1, rv2, rv3, rd;
	char ver[45];
#ifdef ADD_VERSION
	char *new_version = NULL;
#endif
	sscanf(PATCHLEVEL, "%2d%2d%2d%1d%1d%2d%2d",
				&ve, &re, &mi, &rv1, &rv2, &rv3, &rd);
	/* RusNet version */
	sprintf(ver, "%d.%d", rv1, rv2);

	/* minor revision, if any */
	if (rv3)
		sprintf(ver + strlen(ver), ".%d", rv3);

	/* debuglevel, if any */
	if (rd)
		sprintf(ver + strlen(ver), ".d%d", rd);
#ifndef USE_OLD8BIT
	strncat(ver, "/" LOCALE "." CHARSET_8BIT,
			sizeof(ver) - strlen(ver) - 1);
#endif
#ifdef ADD_VERSION
	new_version = MyMalloc(strlen(ADD_VERSION) + strlen(ver) + 1);
	new_version[0] = '\0';
	strcat(new_version, ver);
	strcat(new_version, ADD_VERSION);
	return new_version;
#else
	return mystrdup(ver);
#endif
}

#ifndef CLIENT_COMPILE
#ifdef SEND_ISUPPORT
/*
 * Make ISUPPORT string
 */

char *make_isupport()
{
	static char isupport[200];
	char *p = isupport;
#ifdef SERVER_MAP
	strcpy(isupport,"MAP ");
	p +=4;
#endif
	sprintf(p, "PREFIX=(ohv)@%%+ CHANTYPES=#&!+ CODEPAGES FNC "
		"CHANMODES=beI,k,l,acimnpqrRstz EXCEPTS=e INVEX=I MODES=%d "
		"MAXCHANNELS=%d CASEMAPPING=ascii NICKLEN=%d TOPICLEN=%d "
		"KICKLEN=%d NETWORK=%s ", MAXMODEPARAMS, MAXCHANNELSPERUSER,
		NICKLEN, TOPICLEN, TOPICLEN, NETWORKNAME);

	return isupport;
}
#endif
#endif

#ifndef HAVE_TRUNCATE
/* truncate: set a file to a specified length
 * I don't know of any UNIX that doesn't have truncate, but CYGWIN32 beta18
 * doesn't have it.  -krys
 * Replacement version from Dave Miller.
 */
int truncate(path, length)
const char *path;
off_t length;
{
	int fd, res;
	fd = open(path, O_WRONLY);
	if (fd == -1)
		return -1;
	res = ftruncate(fd, length);
	close(fd);
	return res;
}
#endif /* HAVE_TRUNCATE */

#if SOLARIS_2_3
/* 
 * On Solaris 2.3 (SunOS 5.3) systems, gethostbyname() has a bug, it always
 * returns null in h->aliases.  Workaround: use the undocumented
 * _switch_gethostbyname_r(...).
 */
#define HBUFSIZE 4096

struct hostent *solaris_gethostbyname(name)
     const char *name;
{
  static struct hostent hp;
  static char buf[HBUFSIZE];
  
  return _switch_gethostbyname_r(name, &hp, buf, sizeof(buf), &h_errno);
}
#endif /* SOLARIS_2_3 */

#if HAVE_MEMCMP && MEMCMP_BROKEN
/*
 * Some OS may have a memcmp that is not 8-bit clean.
 *
 * Copyright (C) 1991, 1993, 1995 Free Software Foundation, Inc.
 * Contributed by Torbjorn Granlund (tege@sics.se).
 *
 * NOTE: The canonical source of this part of the file is maintained with the
 * GNU C Library. Bugs can be reported to bug-glibc@prep.ai.mit.edu.
 */

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  Must be an unsigned type.  */
#define	op_t	unsigned long int
#define OPSIZ	(sizeof(op_t))

/* Threshold value for when to enter the unrolled loops.  */
#define	OP_T_THRES	16

/* Type to use for unaligned operations.  */
typedef unsigned char byte;

#if ! defined(WORDS_BIGENDIAN)
#define MERGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))
#else
#define MERGE(w0, sh_1, w1, sh_2) (((w0) << (sh_1)) | ((w1) >> (sh_2)))
#endif

#if WORDS_BIGENDIAN
#define CMP_LT_OR_GT(a, b) ((a) > (b) ? 1 : -1)
#else
#define CMP_LT_OR_GT(a, b) memcmp_bytes ((a), (b))
#endif

/* BE VERY CAREFUL IF YOU CHANGE THIS CODE!  */

/* The strategy of this memcmp is:

   1. Compare bytes until one of the block pointers is aligned.

   2. Compare using memcmp_common_alignment or
      memcmp_not_common_alignment, regarding the alignment of the other
      block after the initial byte operations.  The maximum number of
      full words (of type op_t) are compared in this way.

   3. Compare the few remaining bytes.  */

#if ! defined(WORDS_BIGENDIAN)
/* memcmp_bytes -- Compare A and B bytewise in the byte order of the machine.
   A and B are known to be different.
   This is needed only on little-endian machines.  */
#ifdef  __GNUC__
__inline
#endif
static int
memcmp_bytes (a, b)
     op_t a, b;
{
  long int srcp1 = (long int) &a;
  long int srcp2 = (long int) &b;
  op_t a0, b0;

  do
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
    }
  while (a0 == b0);
  return a0 - b0;
}
#endif

/* memcmp_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN `op_t'
   objects (not LEN bytes!).  Both SRCP1 and SRCP2 should be aligned for
   memory operations on `op_t's.  */
#ifdef	__GNUC__
__inline
#endif
static int
memcmp_common_alignment (srcp1, srcp2, len)
     long int srcp1;
     long int srcp2;
     size_t len;
{
  op_t a0, a1;
  op_t b0, b1;

  switch (len % 4)
    {
    case 2:
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      srcp1 -= 2 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      goto do1;
    case 3:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 -= OPSIZ;
      srcp2 -= OPSIZ;
      len += 1;
      goto do2;
    case 0:
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	return 0;
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      goto do3;
    case 1:
      a1 = ((op_t *) srcp1)[0];
      b1 = ((op_t *) srcp2)[0];
      srcp1 += OPSIZ;
      srcp2 += OPSIZ;
      len -= 1;
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	goto do0;
      /* Fall through.  */
    }

  do
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      if (a1 != b1)
	return CMP_LT_OR_GT (a1, b1);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      if (a0 != b0)
	return CMP_LT_OR_GT (a0, b0);

    do2:
      a0 = ((op_t *) srcp1)[2];
      b0 = ((op_t *) srcp2)[2];
      if (a1 != b1)
	return CMP_LT_OR_GT (a1, b1);

    do1:
      a1 = ((op_t *) srcp1)[3];
      b1 = ((op_t *) srcp2)[3];
      if (a0 != b0)
	return CMP_LT_OR_GT (a0, b0);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  while (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  if (a1 != b1)
    return CMP_LT_OR_GT (a1, b1);
  return 0;
}

/* memcmp_not_common_alignment -- Compare blocks at SRCP1 and SRCP2 with LEN
   `op_t' objects (not LEN bytes!).  SRCP2 should be aligned for memory
   operations on `op_t', but SRCP1 *should be unaligned*.  */
#ifdef	__GNUC__
__inline
#endif
static int
memcmp_not_common_alignment (srcp1, srcp2, len)
     long int srcp1;
     long int srcp2;
     size_t len;
{
  op_t a0, a1, a2, a3;
  op_t b0, b1, b2, b3;
  op_t x;
  int shl, shr;

  /* Calculate how to shift a word read at the memory operation
     aligned srcp1 to make it aligned for comparison.  */

  shl = 8 * (srcp1 % OPSIZ);
  shr = 8 * OPSIZ - shl;

  /* Make SRCP1 aligned by rounding it down to the beginning of the `op_t'
     it points in the middle of.  */
  srcp1 &= -OPSIZ;

  switch (len % 4)
    {
    case 2:
      a1 = ((op_t *) srcp1)[0];
      a2 = ((op_t *) srcp1)[1];
      b2 = ((op_t *) srcp2)[0];
      srcp1 -= 1 * OPSIZ;
      srcp2 -= 2 * OPSIZ;
      len += 2;
      goto do1;
    case 3:
      a0 = ((op_t *) srcp1)[0];
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[0];
      srcp2 -= 1 * OPSIZ;
      len += 1;
      goto do2;
    case 0:
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	return 0;
      a3 = ((op_t *) srcp1)[0];
      a0 = ((op_t *) srcp1)[1];
      b0 = ((op_t *) srcp2)[0];
      srcp1 += 1 * OPSIZ;
      goto do3;
    case 1:
      a2 = ((op_t *) srcp1)[0];
      a3 = ((op_t *) srcp1)[1];
      b3 = ((op_t *) srcp2)[0];
      srcp1 += 2 * OPSIZ;
      srcp2 += 1 * OPSIZ;
      len -= 1;
      if (OP_T_THRES <= 3 * OPSIZ && len == 0)
	goto do0;
      /* Fall through.  */
    }

  do
    {
      a0 = ((op_t *) srcp1)[0];
      b0 = ((op_t *) srcp2)[0];
      x = MERGE(a2, shl, a3, shr);
      if (x != b3)
	return CMP_LT_OR_GT (x, b3);

    do3:
      a1 = ((op_t *) srcp1)[1];
      b1 = ((op_t *) srcp2)[1];
      x = MERGE(a3, shl, a0, shr);
      if (x != b0)
	return CMP_LT_OR_GT (x, b0);

    do2:
      a2 = ((op_t *) srcp1)[2];
      b2 = ((op_t *) srcp2)[2];
      x = MERGE(a0, shl, a1, shr);
      if (x != b1)
	return CMP_LT_OR_GT (x, b1);

    do1:
      a3 = ((op_t *) srcp1)[3];
      b3 = ((op_t *) srcp2)[3];
      x = MERGE(a1, shl, a2, shr);
      if (x != b2)
	return CMP_LT_OR_GT (x, b2);

      srcp1 += 4 * OPSIZ;
      srcp2 += 4 * OPSIZ;
      len -= 4;
    }
  while (len != 0);

  /* This is the right position for do0.  Please don't move
     it into the loop.  */
 do0:
  x = MERGE(a2, shl, a3, shr);
  if (x != b3)
    return CMP_LT_OR_GT (x, b3);
  return 0;
}

int
irc_memcmp (s1, s2, len)
     const __ptr_t s1;
     const __ptr_t s2;
     size_t len;
{
  op_t a0;
  op_t b0;
  long int srcp1 = (long int) s1;
  long int srcp2 = (long int) s2;
  op_t res;

  if (len >= OP_T_THRES)
    {
      /* There are at least some bytes to compare.  No need to test
	 for LEN == 0 in this alignment loop.  */
      while (srcp2 % OPSIZ != 0)
	{
	  a0 = ((byte *) srcp1)[0];
	  b0 = ((byte *) srcp2)[0];
	  srcp1 += 1;
	  srcp2 += 1;
	  res = a0 - b0;
	  if (res != 0)
	    return res;
	  len -= 1;
	}

      /* SRCP2 is now aligned for memory operations on `op_t'.
	 SRCP1 alignment determines if we can do a simple,
	 aligned compare or need to shuffle bits.  */

      if (srcp1 % OPSIZ == 0)
	res = memcmp_common_alignment (srcp1, srcp2, len / OPSIZ);
      else
	res = memcmp_not_common_alignment (srcp1, srcp2, len / OPSIZ);
      if (res != 0)
	return res;

      /* Number of bytes remaining in the interval [0..OPSIZ-1].  */
      srcp1 += len & -OPSIZ;
      srcp2 += len & -OPSIZ;
      len %= OPSIZ;
    }

  /* There are just a few bytes to compare.  Use byte memory operations.  */
  while (len != 0)
    {
      a0 = ((byte *) srcp1)[0];
      b0 = ((byte *) srcp2)[0];
      srcp1 += 1;
      srcp2 += 1;
      res = a0 - b0;
      if (res != 0)
	return res;
      len -= 1;
    }

  return 0;
}
#endif /* HAVE_MEMCMP && MEMCMP_BROKEN */

size_t unistrcut (char *line, size_t maxchars)
{
  size_t len = strlen(line);

  if (len > maxchars)		/* may be it's already ok */
  {
#if !defined(CLIENT_COMPILE) && !defined(USE_OLD8BIT)
    if (UseUnicode > 0)		/* let's count chars - works for utf* only!!! */
    {
      register size_t chsize = 0;
      register char *ch = line;
      register char *chmax = &line[len];

      while (chsize < maxchars && ch < chmax && *ch) /* go for max chars */
      {
	if ((*ch++ & 0xc0) == 0xc0)		/* first multibyte octet */
	  while ((*ch & 0xc0) == 0x80 && ch < chmax)
	    ch++;				/* skip rest of octets */
	chsize++;				/* char counted */
      }
      len = ch - line;
    }
    else			/* 8bit encoding - just let's cut it */
#endif
	len = maxchars;

    line[len] = '\0';
  }
  return len;
}
