/* 
** Copyright (c) 1998 [RusNet IRC Network]
**
** File     : rusnet.h
** Desc.    : rusnet specific commands
**
** This program is distributed under the GNU General Public License in the 
** hope that it will be useful, but without any warranty. Without even the 
** implied warranty of merchantability or fitness for a particular purpose. 
** See the GNU General Public License for details.
 */
#ifndef _RUSNET_H_
#define _RUSNET_H_

/* RusNet extensions */
#if	defined(INET6) && defined(USE_VHOST6)
#define	VHOST6_SUFFIX	".ip"
#endif	/* INET6 && VHOST6 */

#ifdef USE_OLD8BIT
#define RUSNET_DIR_INCOMING 1
#define RUSNET_DIR_OUTGOING 2

#define MAX_CODEPAGE_NAME_LENGTH 16

struct Codepage
{
    int handle;
    int port;
    char id[MAX_CODEPAGE_NAME_LENGTH];
    void *incoming;
    void *outgoing;
   
    struct Codepage *nextptr;
};

int rusnet_getclientport(int);
void rusnet_translate(struct Codepage *, unsigned char, unsigned char *, 
                      int);
unsigned char rusnet_codepage_register(char *, char *, char *, char *);
unsigned char rusnet_codepage_free(void);
struct Codepage *rusnet_getptrbyport(unsigned port);
struct Codepage *rusnet_getptrbyname(char *);

int  rusnet_isvalid(unsigned int);

void initialize_rusnet(char *);
#else
#include "conversion.h"
#endif

aChannel *rusnet_zmodecheck(struct Client *, char *);
void rusnet_add_route(char *, char *, char *);
void rusnet_free_routes(void);
int rusnet_bind_interface_address(int, struct SOCKADDR_IN *, char *, size_t);

#endif
