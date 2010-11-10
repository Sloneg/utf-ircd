��������: ���� ���� ����� ���� ������������ ����, �������� ChangeLog
--------------------------------------------------------------------------
������ 1.5.12
-------------
2010-09-10 LoSt <andrej@rep.kiev.ua>
	* common/common_def.h: ��������� ����������� towupper() ��� ������
		� ������ ���������� UTF8
	* common/conversion.c: ����� toupper() ����Σ� �� ����� towupper()
		��� ���������� ������� � ������������� ���������
	* support/configure.in, support/configure, support/setup.h.in:
		��������� ����������� towupper()

������ 1.5.11
-------------
2010-09-08 erra <erra@ya.ru>
	* iserv/iserv.c: ��������� �������� (����� fopen)

2010-09-08 LoSt <andrej@rep.kiev.ua>
	* ircd/s_bsd.c, ircd/s_conf.c, ircd/s_serv.c: ���������� ������
		������������ ��� ���������� ������ ��������������� ����������
		��������� ����� P:
	* ircd/s_misc.c: �����Σ� ����� realloc ��� ������ �������������
		���������� ������������ �� ��������� � �������
		set_internal_encoding()

������ 1.5.10
-------------
2010-07-29 erra <erra@ya.ru>
	* common/support_ext.h, common/support.c: ������� ������� dgets()
		��� ���������� (�������� �� fgets)
	* ircd/chkconf.c: ������� mystrinclude() � simulateM4Include()
	* ircd/config_read.c: ��������� ����� fileio.c �������� �� fileio.h
	* ircd/s_misc.c: ������� dgets() �������� �� fgets() � read_motd() �
		read_rmotd()
	* ircd/fileio.c: ��������� � common/ (������������ � iserv)
	* ircd/fileio.h: ������������ � common/fileio_ext.h (������������
		� iserv)
	* ircd/s_externs.h: �������� fileio_ext.h
	* iserv/i_externs.h: �������� fileio_ext.h
	* iserv/iserv.c: ������� dgets() �������� �� fgets()
		� flushPendingLines()
	* support/Makefile.in: ��������� ���������� fileio.c

2010-07-27 erra <erra@ya.ru>
	* ircd/s_serv.c: /stats P ���� �������� ��� ������� �������������

2010-07-26 LoSt <andrej@rep.kiev.ua>
	* ircd/channel.c: ��������� ����� �������, ����������� � ������
		��������������� �� ������� /rehash ��� ����� ����������
		��������� ircd

������ 1.5.9
-------------
2010-07-26 erra <erra@ya.ru>
	* ircd/s_conf.c: ���������� ��������
	* support/configure: ���������� enableval � �������� iconv ��������
			(��������� ������� �� �������� ipv6)

2010-07-26 kmale <>
	* support/configure.in: ���������� ��������� ���������� enableval
			� �������� ipv6

������ 1.5.8
-------------
2010-07-22 erra <erra@ya.ru>
	* ircd/s_serv.c: � ����� /stats P ��������� ��������� (��� ������
			� iconv)
	* ircd/s_conf.c: ���������� ������� ����� CONF_RLINE � ����������
			���������
	* ircd/s_bsd.c: ��������� #ifdef � ������� add_listener()
	* ircd/s_misc.c, rusnet-doc/INSTALL: ���������� ��������

������ 1.5.7
-------------
2010-07-22 denk <denis@tambov.ru>
	* rusnet/rusnet.h, rusnet/rusnet_virtual.c: ������� ����� F:
		��������������� ��� IPv6

������ 1.5.6
-------------
2010-07-21 LoSt <andrej@rep.kiev.ua>
	* common/conversion.c, support/configure, support/configure.in,
		support/setup.h.in: ��������� ����������� TRANSLIT_IGNORE
				��� ���������� �������� ���������� iconv

������ 1.5.5
-------------
2010-07-20 denk <denis@tambov.ru>
	* iserv/iserv.c, iserv/i_io.c: ����������� ������������ �����������
		����� � ircd.conf ��� IPv6

������ 1.5.4
-------------
2010-07-12 LoSt <andrej@rep.kiev.ua>
	* support/configure, support/configure.in: ��������� ����
		��������������
	* common/conversion.c: ��������� ����� ��������������

������ 1.5.3
-------------
2010-07-09 erra <erra@ya.ru>
	* common/support.c: ����� ������ �����������. �������� �����
			������ � ��������� ��� ������ � ���������� Unicode

������ 1.5.2
-------------
2010-07-06 
	* common/match.c: ��������� �������� ���������� ��� ������ \\*

������ 1.5.1
-------------
2010-07-02 LoSt <andrej@rep.kiev.ua>
	* common/support.c, common/support_ext.h, ircd/channel.c,
		ircd/s_conf.c, ircd/s_serv.c, ircd/s_service.c,
		ircd/s_user.c , ircd/whowas.c , ircd/whowas_def.h:
		���������� ��������� ���������� � ������������
	* common/conversion.c: �������� �������������� ������������
		�������� RFC 2822 ({}| ����� �� ����� []\) � �����
		������������� � RusNet-1.4

������ 1.5.0
-------------
2009-11-27 LoSt <andrej@rep.kiev.ua>
	* common/struct_def.h: ������ ������ �������� ��� ������������ ���������

1.5.0p20
2009-10-19 erra <erra@ya.ru>
	* common/bsd.c, common/bsd_ext.h: �������� �, �������������, �������
	* common/send_ext.h: ������� ���������� ���������� EXTERN
			������� deliver_it
	* ircd/s_user.c: �������, ������������ ������ IPv4, ������ ���������
			���������� � �������� IPv6; ifdef RUSNET_RLINES
			� send_whois() �����ޣ� �� �� �������� � ���� ���������
			ifdef USE_OLD8BIT, ������������ �������� �����������
			��������

1.5.0p19
2009-09-25 erra <erra@ya.ru>
	* iauth/a_io.c: ������� ���������� minus_one

2009-09-21 erra <erra@ya.ru>
	* ircd/s_user.c: ���� ��� IPv6 � ������ +X by denk
	* ircd/s_bsd.c, ircd/s_conf.c, common/os.h: ���������� minus_one
			������� by denk

1.5.0p18
2009-07-21 erra <erra@ya.ru>
	* rusnet/rusnet_virtual.c: ��� ������ memset() �������� ����� �������
		bzero() (������� �������� ������������ ������ � 64-������
		������������)

2009-06-02 erra <erra@ya.ru>
	* ircd/s_user.c: ����� exit_client() ��� ������ ��������

2009-05-22 erra <erra@ya.ru>
	* ircd/s_serv.c: ��������� ��������, ����������� ��� RusNet ircd
	* ircd/list.c: �������������� ��������� ���������� ���������
	* ircd/channel.c: ������ NJOIN ���������� �� &ERRORS �� ������
		� ���������� ������

1.5.0p17
2008-10-10 erra <erra@ya.ru>
	* ircd/s_conf.c: ������������ ���������� ������� detach_conf()
	* ircd/s_misc.c: ��������� ������� �������� MyConnect(sptr)

1.5.0p16
2008-10-03 erra <erra@ya.ru>
	* ircd/s_bsd.c: catching bugs: verify strerror_ssl against "Success".

2008-09-17 erra <erra@ya.ru>
	* ircd/s_conf.c: code clearance: do not leave unfreed aconf when
		there are clients; copy clients from aconf to bconf for
		SSL connections

1.5.0p15
2008-09-12 erra <erra@ya.ru>
	* *: 1.4.x branch merged.

2008-09-12 LoSt <andrej@rep.kiev.ua>
	* ircd/s_user.c: server flags string len increased by one to pass
		the complete flag set

1.5.0p12
2007-02-06 LoSt <andrej@rep.kiev.ua>
	* ircd/s_err.c: changed RPL_CODEPAGE message (it was requested by
	  alexey@kvirc.ru).
	* ircd/channel.c: fixed channel modes that were lost in transit.

1.5.0p11
2006-04-27 LoSt <andrej@rep.kiev.ua>
	* common/conversion.c: fixed coredump due to not-nullified prev member
	  in conversion_t structure.

2006-03-17 LoSt <andrej@rep.kiev.ua>
	* common/channel.c, common/hash.c: fixed channel name length (might be
	  in bytes instead of chars), got NJOIN protocol errors due to of that.
	* common/channel.c: channel name might be changed in get_channel() so
	  fixed it in m_join().

2006-03-09 LoSt <andrej@rep.kiev.ua>
	* common/packet.c: implemented validation of UTF input since we cannot
	  trust users, they may send invalid UTF strings. :(

2006-02-20 LoSt <andrej@rep.kiev.ua>
	* common/match*, common/common_def.h, ircd/channel.c, ircd/ircd.c:
	  rewritten validation via implemented validtab[].
	* common/send.c, support/Makefile.in, support/configure.in: cosmetic
	  fixes.

2006-02-14 LoSt <andrej@rep.kiev.ua>
	* ircd/channel.c: fixed channel invalidation when internal charset is
	  CHARSET_8BIT.
	* ircd/s_conf.c, ircd/s_bsd.c, ircd/s_bsd_ext.h: listening ports may
	  be reused with the same port but changed P:line or p:line on REHASH.

1.5.0p8
2006-01-26 LoSt <andrej@rep.kiev.ua>
	* common/conversion.c: fixed bug with state of mbtowc().
	* ircd/channel.c: fixed debug message in get_channel().
	* ircd/ircd.c, ircd/ircd_s.h, ircd/s_conf.c: close and open debugfile
	  on -SIGHUP to enable log rotation.

2006-01-18 LoSt <andrej@rep.kiev.ua>
	* common/common_def.h: don't use isalnum() when strict locales asked
	* ircd/s_serv.c: double charset conversion removed

1.5.0p7
2006-01-17 erra <erra@rinet.ru>
	* *: add-ons from LoSt imported
	* ircd/res.c: JAIL_RESOLVER_HACK narrowed to INET4. Currently
		this version won't compile with --enable-ipv6
	* common/conversion.c: minor syntax fix to MyFree() call

2006-01-16 erra <erra@rinet.ru>
	* *: redone merge into 1.4.3 release

1.5.0p6
2005-06-20 LoSt <andrej@rep.kiev.ua>
	* *: merged with 1.4.3 version - it's need to be checked now!

1.5.0p5
2005-06-18 LoSt <andrej@rep.kiev.ua>
	* *: added USE_OLD8BIT definition to easy merge with 1.4.3 versions.
	  deprecated files are findable by checking configure.in and
	  Makefile.in for @oldconvobjs@

1.5.0p4
2005-02-14 LoSt <andrej@rep.kiev.ua>
	* *: bugfixes from 1.4.2_3

2004-11-30 LoSt <andrej@rep.kiev.ua>
	* common/match.c: fixed bug with '?' in hostmask - it's not byte
	  in multibyte

2004-11-06 LoSt <andrej@rep.kiev.ua>
	* ircd/channel.c: fixed SIGBUS with unistrcut() on /part

1.5.0p3
2004-11-05 LoSt <andrej@rep.kiev.ua>
	* support/config.h.in, ircd/ircd.c, ircd/s_bsd.c, ircd/s_conf.c, ircd/s_debug.c, ircd/s_misc.c, ircd/s_user.c, ircd/ircd_signal.c, common/send.c, common/send_ext.h:
	  rewritten all logging mechanics, introduced g: lines for logging

1.5.0p2
2004-11-04 LoSt <andrej@rep.kiev.ua>
	* ircd/ircd.c, ircd/ircd_ext.h, ircd/s_conf.c, ircd/s_misc.c, ircd/s_serv.c:
	  added charset selection for ircd.conf and ircd.mord
	* ircd/s_debug.c: updated VERSION reply with new configuration options

2004-11-01 LoSt <andrej@rep.kiev.ua>
	* ircd/channel.c, ircd/s_user.c, common/support.c, common/support_ext.h:
	  fixed bug with topic/reasons length (i.e. in chars)
	* rusnet/rusnet_cmds.c: change nick on client side after /codepage
	* common/msg_def.h, common/parse.c: added command /charset in addition
	  to /codepage

1.5.0p1
2004-10-27 LoSt <andrej@rep.kiev.ua>
	* ?: fixed bug with limitation of 512 bytes per send everywhere (RFC
	  says: chars)
	* *: moved conversion* to common/ directory and get rid of unused files

2004-10-22 LoSt <andrej@rep.kiev.ua>
	* common/send.c, conversion.c, support/config.h.dist: fixed
	  "No text to send" from 8bit server links, added DO_TEXT_REPLACE mode

2004-10-05 LoSt <andrej@rep.kiev.ua>
	* *: updated to 1.4.2pre_20

1.5.0p0
2003-09-29 LoSt <andrej@rep.kiev.ua>
	* *: added UTF-8 negotiation to server link protocol
	   - get rid of rest of rusnet.conf and translations tables
	   - changed chname for aChannel to dynamically allocated
	   - added uppercase fields to structures for fast nicks comparisons

Version 1.4.12
-------------
2008-09-08 erra <erra@ya.ru>
	* ircd/s_bsd.c: code clearance: check results for set_sock_opts for
		SSL connections; call close_conection() instead of repeating
		portions of code.

Version 1.4.11
-------------
2008-08-25 erra <erra@ya.ru>
	* ircd/channel.c: code clearance: return NULL in get_channel() when
		CREATE was not defined; free newly created channel in m_join()
		when can_join() failed; do not attempt to create channel if
		IsChannelName() fails in m_njoin()
	* ircd/s_bsd.c: code clearance: close fd (optionally) and free cptr
		when bind failed. While it should never happen, the action
		must be proper, anyway.
	* ircd/ircd.c, irc/s_serv.c, ircd/s_user.c: SetRMode() call moved
		to do_restrict
	* ircd/s_conf.c: do not double '%' prefix when R-line is renewed;
		set prefix only when NO_PREFIX is unset

Version 1.4.10
-------------
2008-07-02 skold <skold@anarxi.st>
	* ircd/s_user.c, s_err.c, common/numeric_def.h: test links KILL patch
		removed from code. Surely you are not saying you can undo
		kills on the server that issued them without having desync.
		You can't stop the damage already been done on the test server.
		The only solution here is to squit the test server in response
		to remote kill
	* ircd/s_serv.c, s_err.c, common/numeric_def.h: SQUIT disabling logic
		has been re-written so it wouldn't cause servers desync across
		network

������ 1.4.9
-------------
2008-06-19 erra <erra@ya.ru>
	* ircd/s_serv.c: ������� SQUIT ������� ����������� ��� ��������
		��������
	* ircd/s_user.c: ������� KILL ������� ����������� ��� ��������
		��������
	* common/numeric_def.h: ��������� ERR_TESTCANTKILL � ERR_TEST_CANTSQUIT
	* doc/example.conf: ��������� �������� �������� ��������� �������
		� �������� ����� N:

������ 1.4.8
-------------
2008-05-16 erra <erra@ya.ru>
	* ircd/channel.c: ����� &ISERV ������ ��� ������� ����, �����
		���������� ����

2008-04-21 erra <erra@ya.ru>
	* ircd/whowas.c: ������������� �����Σ� ����� ��������� �� �������
		������� � ������� release_locks_byserver()

������ 1.4.7
-------------
2008-03-31 Adel <adel.abouchaev@gmail.com>
	* ircd/whowas.c: �����Σ� ����� ��������� �� ������� �������
		� ������� release_locks_byserver()

������ 1.4.6
-------------
2008-03-04 erra <erra@ya.ru>
	* ircd/s_user.c: ������������� ��������� �������� +x � ������
		����������� � ����, ���� ������ NO_DIRECT_VHOST; ���������
		������� �������� � ��������������� ������������� ('?' � '*')

������ 1.4.5
-------------
2008-02-04 erra <erra@ya.ru>
	* ircd/s_misc.c: ��������� ������ ������������ ������ � ��������
		get_client_name � get_client_host (cptr->auth)

������ 1.4.4
-------------
2007-09-13 skold <skold@anarxi.st>
	* ircd/channel.c: ����� m_invite() ������ ���������� ��� �������������
		� ������ +b
	* support/configure.in: ����������� zlib ����������,
		����������� openssl ��������

������ 1.4.3
-------------
1.4.3_028 (R1_4_3_028)
2006-02-10 cj <cj@deware.com>
	* ircd/s_user.c: ���������������� ����� +R ������������ � +b
	* ircd/s_conf_ext.h: �������� find_kill()
	
1.4.3_027 (R1_4_3_027)
2006-01-20 erra <erra@rinet.ru>
	* ircd/channel.c: ���������� ������ ���������� � ������ �������������
		������� ��������� � ����: is_chan_op() ��������� �������
		������ (������ ��������� � ������� ������������� 2005-08-24)
	* ircd/s_err.c: ���������������� ����� +R ��� �������� ������� �
		������ �������

1.4.3_026 (R1_4_3_026)
2006-01-20 erra <erra@rinet.ru>
	* ircd/channel.c: ����� mbuf � m_njoin() ��������� �� 1 ���
		��������������; ����� ������������� ����� �� ����� ����������
		��� ������� ���������

2006-01-19 erra <erra@rinet.ru>
	* ircd/channel.c: �������� ���/����� ��� ������������� ������
		��������� NJOIN

1.4.3_025 (R1_4_3_025)
2006-01-09 cj <cj@deware.com>
	* ircd/s_conf.c: ����������� ������������ ������ ��� ��������
		���������� ����� K/R/E

1.4.3_024 (R1_4_3_024)
2005-12-26 slcio <silence@irc.run.net>
	* common/common_def.h: �������� � ��������� ���������� �������� �
		isvalid()

1.4.3_023 (R1_4_3_023)
2005-12-24 slcio <silence@irc.run.net>
	* ircd/s_serv.c: ���������� ������ K/R �� ��������, �� �����������
		��� ������, ��� �� ����� �����������

1.4.3_022
2005-12-20 erra <erra@rinet.ru>
	* ircd/ssl.c: ��������� ������������� ������� ���������� � ������
			strncpy() ����������

2005-12-20 cj <cj@deware.com>
	* ircd/ssl.c: ��������� ������� ������� ������ SSL

1.4.3_021 (R1_4_3_021 RC6)
2005-12-19 erra <erra@rinet.ru>
	* common/support.c: ����� strcpy() ������� �� strncpy() � myctime()

2006-01-20 lost <LoSt@lucky.net>
	* ircd/s_misc.c: �������� ������� ������ \r � \n �� \0 ���������

1.4.3_021 (R1_4_3_021 RC6)
2005-12-18 cj <cj@deware.com> (from skold)
	* common/msg_def.h, parse.c, ircd/s_serv.c, s_serv_ext.h: �������
			��������� EOB/EOBACK ��� ������������� � ��������
			��������

2005-12-18 cj <cj@deware.com>
	* common/send.c: �� ������� ������� ���������� ���-����� � ���������
			���

2005-12-16 erra <erra@rinet.ru>
	* configure: ���������� �������� ���������� � �������� configure.
	* common/support.c: ������ ����������� � ������ PATCHLEVEL
			������������� �� ������ 1.5.0
	* ircd/s_conf.c: ����� dgets() ���̣� ��� ����������

2005-12-16 cj <cj@deware.com> (from Umka)
	* ircd/ircd.c: ����������� ��� ������������� #ifdef IRC_UID

2005-12-14 erra <erra@rinet.ru>
	* ircd/s_user.c: �������� ������� ��� ��������� ���� � send_whois()
			����� �������� ����������

2005-12-13 erra <erra@rinet.ru>
	* ircd/s_user.c: ����������� ���������� ��� ������� ������� ������,
			���������� \d+-\d+ inside - ��� �������� �����

1.4.3_020 (R1_4_3_020 RC6)
2005-12-08 slcio <silence@irc.run.net>
	* support/configure.in, configure: ������ ��� Solaris-2.8 (SunOS 5.8)
			�� ������� ������������� libcrypt ������ openssl
			libcrypto.
	* common/support.c: ����������� ��������� ����� ������ � ������ ������
	* ircd/s_serv.c: ����� 'L' � m_stats() ��������� � 'N', L ���������
			��� ���������� �� �����

2005-12-04 slcio <silence@irc.run.net>
	* support/config.h.dist, ircd/s_serv.c: USE_TKSERV �������� ��
			USE_SERVICES, ����� ��������� ������������� USE_SERVICES
			��� tkserv.
	* ircd/channel.c, support/config.h.dist: ��������� �����������
			JOIN_NOTICES ��� �������� ������� ����� �� ������
			��������� ��������
	* ircd/s_misc.c: � ��� &OPER ��������� ������ ����� ��������� ��������
	* ircd/ircd.c, ircd/s_serv.c, ircd/s_user.c: ��������� ���������
			������� kline/rline

2005-11-14 erra <erra@rinet.ru>
	* ircd/channel.c: �������� ���������� ������ ������� +o/+h � ������
			����� �������� �ݣ � ������������.

1.4.3_019 (R1_4_3_019 RC5)
2005-11-13 cj <cj@deware.com>
	* ircd/channel.c: ���������� ������� m_invite(), ��� ��������
			�������� �������� ����������� �� ������. ����������
			�� ���� ������ ����� � ����� �������������.

1.4.3_018 (R1_4_3_018 RC4)
2005-11-03 cj <cj@deware.com>
	* iserv/i_log.c: �������� ����� � LOG_DAEMON �� LOG_FACILITY �
			������� openlog() ��� syslog.

2005-11-02 cj <cj@deware.com> (from slcio <silence@irc.run.net>)
	* ircd/s_bsd.c: ������������ ������������� free_server() �
			������� connect_server(): ������ ������������ ��������
			�� ����������, ����� ���������� ����������. ��� �����
			��������� � ����������� ������ � ������� m_server().

2005-11-01 cj <cj@deware.com>
	* ircd/ssl.c, s_bsd.c, ircd.c, ircd_ext.h: ��������� � �������
			���������� �������� ����������� SSL, ���� ����������
			IsSSL. ��������� ����������� � ssl_fatal() ���� ���
			���� ��������� ��������� ���������� SSL-����������.

2005-11-01 erra <erra@rinet.ru>
	* ircd/s_conf.c: �������� �������� ����� � ������� N: � ������, ����
			����� ����� 4 (��������, ����� �����)

1.4.3_017 (R1_4_3_017 RC3)
2005-10-21 erra <erra@rinet.ru>
	* common/send.c: ������ ���������� �� ����� dup() ������ ��������
			� ���������� ��������� �������� ������������

1.4.3_016 (R1_4_3_016 RC2)
2005-10-13 cj <cj@deware.com>
	* ircd/s_user.c: ���������� ������������� �����  ClearWallops(x),
			��������� ����������� ����������������� ������ +w
			������ ��� ����������

2005-10-13 erra <erra@rinet.ru>
	* ircd/s_serv.c: ������ sendto_ops_butone �������� �� ������
			sendto_serv_butone ��� WALLOPS_TO_CHANNEL
	* common/send.c, common/send_ext.h: ������� sendto_ops_butone
			��������� ��� WALLOPS_TO_CHANNEL
	* common/struct_def.h, common/numeric_def.h, ircd/s_err.c,
	  ircd/s_user.c: ����� ����������������� ������ +w � ����������
			��� ����� &WALLOPS ��� WALLOPS_TO_CHANNEL

2005-10-12 erra <erra@rinet.ru>
	* common/send.c: sendto_ops_butone ���������� � ����������� ���� �
			��������� ��������������
	* ircd/s_serv.c: ������ sendto_ops_butone �������������� ��������
			sendto_flag(SCH_WALLOPS...) ��� WALLOPS_TO_CHANNEL

1.4.3_015 (R1_4_3_015 RC1)

2005-09-27 skold <chourf@deware.com>
	* Modified Files
	  common/struct_def.h common/sys_def.h
	  ircd/chkconf.c ircd/ircd.c ircd/s_conf.c ircd/s_conf_ext.h
	  ircd/s_serv.c ircd/s_user.c support/Makefile.in
	* Added Files
	  ircd/config_read.c, fileio.c, fileio.h:
		��������� #include �������� ������ �� ratbox, ����� �� 2.11
	* ircd/s_user.c/m_umode(): 'S' �� ���������� �� 's' � �����������
		����������������� ������ ssl

2005-09-23 skold <chourf@deware.com>
	* common/struct_def.h ircd/ircd.c ircd/s_conf.c ircd/s_serv.c
	  ircd/s_user.c rusnet-doc/ChangeLog.ru rusnet-doc/RELEASE_NOTES:
		��������� ������ ����������� ��� ������������� �����
		������������ (IsRLined �������) � m_trace() (�����
		SendWallops ������������)

2005-09-21 erra <erra@rinet.ru>
	* common/send.c: sendto_log ����������� ���ң�, ����� ��������
			������ ��� ������; ���� ��� ���� ��� ���� ��������
			����������, �� ������������ �����, ����������
			fd �� ���� ��� ������ ���.

1.4.3_014 ()
2005-09-17 skold <chourf@deware.com>
	* common/send.c: ���������� ������������ ������ � sendto_log (slcio)
	* ircd/s_conf.c: ����������� do_restrict() ��� ������������ ('%')
			�������������
	* rusnet/rusnet_cmds.c: ���������������� ����� +h ����� �� ����
		
2005-09-17 skold <chourf@deware.com>
	* ircd/s_serv.c, channel.c, send.c, common/struct_def.h, parse.c, 
		support/config.h.dist: ������� wallops ������ ����� ��������
			��������� � ����� &WALLOPS, ���� ������ ����������
			WALLOPS_TO_CHANNEL.
			������ ��� ������� �������� ����������.
			
2005-09-17 slcio <silence@irc.run.net>
	* common/parse.c, struct_def.h: #define LOCOP_TLINE/OPER_TLINE for
			opers/locops temporary lines management.

2005-09-12 erra <erra@rinet.ru>
	* ircd/s_conf.c, ircd/s_conf_ext.h: ������������ ������ B: �
			���������� ������ ���������� ������ I:, �����
			����������� � B: ������� ��� � ����.

1.4.3_013 (R1_4_3_013)
2005-09-07 skold <chourf@deware.com>
	* ircd/list.c/free_server(),make_server(): ��������� ��������������
			����������� ��������� ������� free()
	* ircd/ircd.c, support/config.h.dist: �������� DISABLE_DOUBLE_CONNECTS
			������������ �� 2.11, ����� ���������� �� ������� �
			����� ���������������� ���� � �����, ������������
			������� try_connections() (���������� �� 2.11)

1.4.3_012 (R1_4_3_012)
2005-09-04 skold <chourf@deware.com>
	* ircd/s_user.c: ���������� ������ ��������������� ��� ����������
			����� �������. ����� � ������� � TLD �� ������
			���������� ������������ ��������. ������ ����� ��
			������������ KILL.

2005-09-03 slcio <silence@irc.run.net>
	* support/Makefile.in: ���������� ������ � codepagedir

2005-09-01 skold <chourf@deware.com>
	* common/send.c, common/send_ext.h, ircd/list.c, s_misc.c, s_user.c,
		s_user_ext.h, support/config.h.dist, common/struct_def.h:
			���������� ������������ ������ � sendto_log(),
			sendto_flog() ����������, ����� �� ���������� �����
			��� �������� � (fd merge). �������� �� ���� ������,
			���� ����������� p11 ��� p10.

1.4.3_011 ()

2005-08-28 slcio <silence@irc.run.net>
	* common/send.c: ������������ �������� vhost � vsendpreprep()

2005-08-27 slcio <silence@irc.run.net>
	* many files: ���������� �� __P()

2005-08-26 skold <chourf@deware.com>
	* support/configure.in, configure: ���������� ������ � -lcrypto, ���
			���������� ���������� �� ��������� �����������
	* common/support.c, support_ext.h: MyFree(char *) �������� ��
			MyFree(void *), gcc-4.x �� ����� �������������
				{(char *)(x) = NULL}.


2005-08-24 erra <erra@rinet.ru>
	* common/struct_def.h, ircd/channel.c, ircd/channel_ext.h,
		ircd/s_user.c: ������ ����� ��������� �����: +h (������������)
	* common/struct_def.h, ircd/s_serv.c: �������� ����� SV_2_11 ���
			����������� �������������: ����������� ��������
			������ ��������� �� 0211 ��� ��������� ������� FORCE
			�� SVSNICK � ����� ������� �������� ������.

2005-08-23 erra <erra@rinet.ru>
	* iauth/mod_dnsbl.c: ��������� ������������� ����� �������
			�� ������ DNS

1.4.3_010 (R1_4_3_010)
2005-08-23 lost <LoSt@lucky.net>
	* ircd/s_serv.s: �������� � ��������� ��������: ��������� �������
			�������� ����������, ���� �� ���������� � �����.
	
2005-08-21 slcio <silence@irc.run.net>
	* common/support.c, iauth/a_io.c, ircd/s_bsd.c, iserv/i_io.c,
		support/Makefile.in, support/config.h.dist, ssl_cert:
			������������ ������� sparc-solaris-2.[7-9] ������
			��������� ��������������.
	    
2005-08-20 skold <chourf@deware.com>, slcio <silence@irc.run.net>
	* support/configure.in, Makefile.in, config.guess, config.h.dist,
		config.sub, configure, setup.h.in, common/os.h: ���������
			��������� configure.in ����������� openssl
			������������, ���������� ������� �������
	* irc/*: ��������� ������� �������
	* ��������� �����: ��� SPRINTF, mystr[n]cmp. strcase[n]cmp ���������
			�� my[n]cmp

2005-08-18 skold <chourf@deware.com>
	* common/struct_def.h, ircd/ircd.c, ircd_ext.h, s_bsd.c, s_bsd_ext.h,
		s_conf.c, s_user.c, ssl.c, ssl.h: ������� �������� SSL,
			���������� ������. ������ � rehash ��� ��������� �
			���������� SSL ��� listener'�. ������� REHASH SSL
			������ ������ �������� �������������� ���������� SSL
			� �����������, � REHASH P ������������� ��� listener'�
			�� ������������. ����������� ��������� P->p � p->P
			�� ���� ��� ������������ �����.

2005-08-17 slcio <silence@irc.run.net>
	* ircd/channel.c: ����������� � ������������� IsRusnetServices().
	* ircd/ssl.c: ���������� ������������ ������ � disable_ssl().
	
2005-08-15 lost <LoSt@lucky.net>
	* common/send.c, send_ext.h, struct_def.h, iauth/a_log_def.h,
		ircd/ircd.c, ircd_signal.c, s_bsd.c, s_conf.c, s_misc.c,
		s_serv.c, s_user.c, iserv/i_log_def.h, support/config.h.dist:
			����� ����� ��������������, ������������� ��
			ircd.conf, � �� config.h.
			����������� � RUSNET_DOC.

2005-08-15 skold <chourf@deware.com>
	* ircd/ircd.c, s_bsd.c: ����������� ��� daemonize() �� 2.11: ��������
			�������� ������������ ��������� � ������������ ������
			������� ����� ��������; ������� ������� BOOT_CONSOLE.

2005-08-14 lost <LoSt@lucky.net>
	* common/common_def.h: ����� isvalid() �������� ��������� ����������
			������� (����������).

1.4.3_009 (R1_4_3_009)

2005-08-12 skold <chourf@deware.com>
	* ircd/ircd.c: ����� daemonize() ��������� �� ������ initconf(). 
			��������� �������� �����������, �� ���� ���������
			������, ����� �������� ������ ��������� stderr (2)
			� ������ ���� ������� ������� fork().

2005-08-10 slcio <silence@irc.run.net>
	* ircd/s_user.c, common/parse.c, struct_def.h: ����� IsRusnetServices()
	* ircd/channel.c, s_user.c: ��������� ���̣���� cmode, kick, topic,
			invite, notice ��� IsRusnetServices()
	* ircd/channel.c: ��������� ���̣���� NAMES ��� IsOper()
	* ircd/s_serv.c: ���������� ����� SSL � report_listeners()
		
2005-08-01 skold <chourf@deware.com>
	* ircd/s_serv.c: ��������� �������� ������� � ������� T, � �� ������
			����� � handle_tline().
			����������� ��� ������������ ���������� ���������
			�������� � sendto_slaves()
			����������� ��� ��������� � ��������� ����� T, ������
			�� �� �������.
			
2005-08-01 skold <chourf@deware.com>
	* common/numeric_def.h, ircd/s_bsd.c, s_err.c, support/config.h.dist: 
			RPL_HELLO ��� �������������������� ��������, ������
			��������� ������� �������� � ������� �� 20
	* common/struct_def.h, irc/c_numeric.c, ircd/ircd.c, s_err.c, s_serv.c:
			RPL_TRACELOG �������
	* common/parse.c, struct_def.h, s_bsd.c, s_bsd_ext.h, s_misc.c,
		s_serv.c: ������ m_reconnect(), close_held(), hold_server()
			�������
	* common/send.c, ircd/s_bsd.c, s_misc.c, s_user.c:
			���������� #ifdef UNIXPORT
	* common/struct_def.h, ircd/ircd.c, s_conf.c, s_misc.c, s_misc_ext.h, 
		s_serv.c, support/config.h.dist: 
			������ CACHED_MOTD �������� �� ���������, read_motd()
			������ ��ģ� ���� ���������, ����� � ����� �����
			��� '\n'.
	* common/struct_def.h, ircd/ircd.c, s_bsd.c, s_conf.c: isListening()
			������������� � isListener()
	* common/struct_def.h, ircd/ircd.c, ircd_ext.h, s_bsd.c, s_bsd_ext.h, 
		s_debug.c, s_misc.c, s_serv.c, support/config.h.dist: 
			�������� DELAY_CLOSE ��� �������� �������� ����������
			������ ������ �������������� �������� ������������
			�� 2.11
	* common/struct_def.h, ircd/s_bsd.c: ���� EXITC_* ������������� ��
			2.11 �� �������
	* common/support.c, support_ext.h, ircd/chkconf.c, s_conf.c,
		iserv/iserv.c: dgets() ��������� ������ (�� 2.11)
	* ircd/channel.c: ������� ����� ������� � ������� PART ����� ����
			��������, ��� ��������� � ���������������� ����.
	* ircd/ircd.c, ircd_ext.h, s_bsd.c: listener'� ������� �� local[] � 
			��������� ������ ListenerLL
	* ircd/ircd.c, s_bsd.c: iauth ������ �������� ��� cygwin, daemonize(), 
			open_debugfile() ������������� �� 2.11
	* ircd/ircd_signal.c: SIGUSR1 ����� �� ������������ iauth
	* ircd/list.c, ircd.c, s_bsd.c, s_conf.c: ���������� �������
			serverbooting ��������� ��� ��������, ���� �� � ���
			�ӣ �ݣ ��������, �� ������� ����� �������� ���������.
	* ircd/s_bsd.c, s_bsd_ext.h: ���� dolisten �������� � inetport()
			��� ������������� � ������� � ������� ����� P:
	* ircd/s_bsd.c, s_bsd_ext.h: ������ open_listener(), reopen_listeners()
			��������� ��� ������ �� ���������� ��������.
	* ircd/s_bsd.c: �������� ������ � iauth �������������� (�������������
			�� 2.11)
	* ircd/s_bsd.c, s_bsd_ext.h: close_client_fd() ��� ��������
			������������ ����������� ������,
			add_connection_refuse() (������������� �� 2.11)
	* ircd/s_bsd.c: close_connection() ��� ���������� ���������� �����
			���� 0, - ��� ���������� �������������� �����������.
	* ircd/s_bsd.c: ����� �������� LISTENER_MAXACCEPT ������ ֣����
			�������� 10 ��� �����������, ��� ����� ����������
			����� ���� ������� ������������.
	* ircd/s_bsd.c, support/config.h.dist: read_message(): LISTENER_DELAY
			��� ��ɣ�� ����� ���������� (������ �� 2.11)
	* ircd/s_serv.c: report_listeners() ��� ��������� ����������� ���������
			������ � ���������� �� STATS P; ������ STATS p �
			STATS P ����������.
	
1.4.3_008 (R1_4_3_008)
2005-06-15 cj <cj@deware.com>
	* ircd/s_conf.c: ���������� ������������ ��������������� � check_tlines()

2005-05-31 cj <cj@deware.com>
	* iserv/iserv.c: �������� ��������� ��������. SIGUSR2 ������
		������������, SIGHUP ������������� ����� ��������/syslog,
		SIGTERM/SIGINT �������� � ������ ������.

2005-05-30 cj <cj@deware.com>
	* ircd/s_user.c, rusnet/rusnet_cmds.c: ���������� ���� ��� m_nick()
		������ ���������� �������� � ���������� �������� ���
		����������������� ������ +r/+R.

2005-05-30 witch <witch@amber.ff.phys.spbu.ru>
	* ircd/s_user.c: m_umode() switch/case ��������� � if/else ���
		������������ ����������� ����������

2005-05-25 skold <chourf@deware.com>
	* common/match.c, struct_def.h, common_def.h: ����� ������ ��������
		������������ �� ���� hybrid, ������ ������ � ������� �����
		��������� �� ������ � ������� �������.
	* ircd/s_serv.c: nonwilds() ������������ �� ���� hybrid ��� ��������
		���������������� �������� ����������.

2005-05-15 skold <chourf@deware.com>
	* ircd/s_conf.c, s_conf_ext.h: find_kill(), find_rline() �������� ��
		check_tlines()
	* ircd/s_serv.c: handle_tline(), sendto_slaves(), send_tline_one(),
		rehash_tline() ��������� ��� ������ � ���������� ��������
		������������.

2005-05-15 silencio <silence@irc.run.net>
	* ircd/s_serv.c: match_tline() ��� �������� ��������� ����� �� �������
	* ircd/s_serv.c: ����� STATS r ������ݣ� � STATS t output. STATS r
		������ ������ STATS R
			
2005-05-13 silencio <silence@irc.run.net>
	* iserv/iserv.c, iserv.h: �������� � ������ � ����������������� �������
	* iserv/iserv.c: �������� � �������� ������������� ������ ����� ������
	* ircd/s_user.c, s_serv.c: �� ���� ������ ��������� � SERVICES_HOST
	* ircd/ircd.c, s_conf.c: ���� USE_SERVICES ����� �� ����, ���������� �
			������� �������� RusNet
	* ircd/*: ���������� �� K: (������ E:) �������� �� ������� �����
			RUSNET_IRCD
	* ircd/ircd.c: checkpings() ���������� check_tlines() ������ �������
			find_kill()
	* ircd/s_conf.c, common/struct_def.h: �������� ���� E ��� ���������
			�� REHASH ���������� �� ������ (����� E:)
	
2005-05-12 skold <chourf@deware.com>
	* iserv/i_log.c, i_log_ext.h, iserv.h: ����������� ��ģ����
			��������������
	* iserv/iserv.c: ������ ����� ������ �� ���� (����� ������ ircd)
	* ircd/s_serv.c, s_serv_ext.h: m_kline() - ��������� ���������� �
			���������� �� �������� rusnet/;
			����� ����������� ������ ��� m_rline(), m_eline(),
			m_ukline(), m_urline(), m_uneline()
	* ircd/s_serv.c, err.c: m_stats() ��������� ����� �������
			RPL_STATSKLINE, RPL_STATSRLINE 
	* ircd/s_conf.c: initconf() ������ ��������� aconf->hold �����������
			� ����� �������� ��������� ����� (tline).
	
2005-05-10 skold <chourf@deware.com>
	* ircd/ircd.c, support/config.h.dist: TIMEDKLINES ������ �� ����
	* ircd/s_conf.c: find_kill() ����������� � ����� � ����� ��������
			����� K:
	* common/match.c, ircd/s_conf.c: match(), match_ipmask(): ����������
		��������� '=' ��� ��������� �ͣ� ������.

2005-05-09 skold <chourf@deware.com>
	* iserv/*, support/Mekafile.in, config.h.dist, ircd/channel.c,
		s_bsd.c, s_conf.c, s_iserv.c, s_iserv_ext.h, common/send.c,
		struct_def.h: ������ iserv ��� ������ tkserv

2005-05-07 silencio <silence@irc.run.net>
	* ircd/ircd.c: main(): iserv, ����������� ircd
	
1.4.3_007 (R1_4_3_007 tag)

2005-04-27 skold <chourf@deware.com>
	* ircd/s_conf.c: rehash() ��������� ��������� resolv.conf ���
			/rehash dns

2005-04-22 skold <chourf@deware.com>
	* common/struct_def.h, ircd/ircd.c, s_conf.c: FLAGS_RLINE � ���
			������������ �������� � ������������ �� �������� R:
	* ircd/s_conf.c: attach_conf() ������ u@h ������ ��� ����� R:
			�� ������� �� I:
	
1.4.3_006 (R1_4_3_006 tag)
2005-04-18 skold <chourf@deware.com>
	* contrib/tkserv/tkserv.c: squery_line() ��������� ������ �� ��������
			R:, ���������� ����������
	* rusnet/rusnet_cmds.c, ircd/s_serv.c, common/struct_def.h: �������
			��������� RLINE
	* common/patchlevel.h, support.c, ircd/s_err.c, ircd.c: make_version()
			������������ ��� RusNet
	* ircd/ircd.c: ����� check_pings() ��� ����� R: �� ������� REHASH
	* ircd/channel.c: ��������� ����������� ������ ��� ������ +R

1.4.3_005 (R1_4_3_005 tag)

2005-03-31 skold <chourf@deware.com>
	* ircd/s_conf.c, s_serv.c: m_rehash(), rehash() ��������� ����������,
			initconf() ��������� �� ������� ������� ���������������
			���������, ���������, ��� ������������
	* ircd/s_conf.c: initconf() �������� ����� #include ����������
			(��������� ������)
	* ircd/s_conf.c, ircd.c, chkconf.c, common/struct_def.h: ������ ������
			R: � ���� CONF_RESTRICTED ������ �� ����

2005-03-26 skold <chourf@deware.com>
	* common/numeric_def.h, struct_def.h, ircd/chkconf.c, s_conf.c,
		s_conf_ext.h, s_err.c, s_user.c: ����������� ������ RusNet R:

2005-03-29 silencio <silence@irc.run.net>
	* support/Makefile.in, config.h.dist, ircd.rmotd: �����ݣ���� motd

1.4.3_003 (-)

2005-03-17 cj <cj@deware.com>
	* support/configure.in, configure: ������ ��� ������ ��� SunOS � Linux

2005-03-19 skold <chourf@deware.com>
	* support/config.h.dist, ircd/s_user.c, channel.c, common/struct_def.h:
		�������� ���������������� ����� +R ��� RusNet

1.4.3_002 (R1_4_3_002 tag)

2003-11-13 cj <cj@deware.com>
	* support/configure.in, acconfig.h, configure, setup.h.in: ������ ���
			����������� OpenSSL
	* support/configure.in, config.h.dist, Makefile.in: �����������
			���������� ��������� ������ � ������ EGD

2003-10-30 skold <chourf@deware.com>
	* common/numeric_def.h, os.h, send.c, send_ext.h, struct_def.h,
		irc/c_defines.h c_externs.h, ircd/chkconf.c, ircd.c,
		ircd_ext.h, s_bsd.c, s_conf.c, s_debug.c, s_err.c, s_externs.h,
		s_serv.c, s_user.c: ��������� �������� ������� SSL
	* support/config.h.dist: �����������/���������, �� ��������� � SSL
	* support/configure.in: ����������� ��������� ��� SSL

1.4.2R (R1_4_2 tag)

2004-12-24 silencio <silence@irc.run.net>
	* ircd/s_user.c/m_nick(): ����������� ��� (NICK 2) ����������� KILL
			�� �������� � ���������

2004-12-07 skold <chourf@deware.com>
	* common/parse.c/parse(): ��� �������� -1 � ������������� ��������
			����Σ� �� 1 (������� ����������� fd)
			���������� (�����) �����������.

2004-12-06 skold <chourf@deware.com>
	* ircd/channel.c/clean_channelname(): ����� � � ��������� koi8-u


1.4.2 (deferred)

2004-10-06 skold <chourf@deware.com>
	* ircd/channel.c: ������ �� ������������� ����� ���������� ���̣�����
			KILL �� ��������� ������
	* ircd/channel.c/clean_channelname(): ������� ������ �������� �������

2004-09-21 erra <erra@rinet.ru>
	* contrib/tkserv/tkserv.c: ��� ��������� ����������� � �������������
			������� � tkserv

2004-09-14 erra <erra@rinet.ru>
	* iauth/mod_dnsbl.c: ���������� ��������� ���� � ��������� ����� �
			����� �����

(1.4.2pre_20)

2004-08-19 skold <chourf@deware.com>
	* channel.c/match_mode_id(): ��������� ������ ������, ���������
			2003-09-24

2004-08-09 skold <chourf@deware.com>
	* ircd/channel.c: ���������� ������ ������������ ������ � pre_18

2004-07-06 erra <erra@rinet.ru>
	* rusnet/rusnet_cmds.c: ������� ���������� �� KLINE � tkserv

2004-05-16 skold <chourf@deware.com>
	* ircd/s_user.c: ���������� ������������ ������ �������
		"KICK #chan me, someone" (������ NJOIN),
		���������� ������������ kill'� �� ���������� ��������,
		���������� KILL � ���������� ��������

2004-05-16 silencio <silence@irc.run.net>
	* ircd/s_user.c: ���������� ������������ ��������� ��������� ��������

2004-05-02:
* ����� ��� ����������� ������  -skold
* ��������� ��� ��� ��������� �� FreeBSD jail  -skold
* ���������� ������������ ������ � ������� add_local_domain()  -skold
* ��������� ����������� �������� �� ����� (+q) ������ ��� �����������
  �� MAXCHANNELSPERUSER  -skold

2004-03-31:
* ��������� ������� STATS ��� ��������� ���������� �� ��ϣ� �������  -skold
* ���������� ���������� user@host ��� ������� STATS o  -skold
* ���������� ������������ ������ � umode +x ��� ������������� ������� (���
  �����)  -erra

2004-02-27:
* ���������� ������������� ������ to<low|up>ertab[] � KOI8  -skold
* ��������� ����������� � ������� ��������� client_flood  -skold

2004-02-24:
* ���������� �������� K/E ����� ����������� tkserv  -erra

2004-02-14:
* � ����� ������ &KILLS ��������� ident@host  -skold
* ���������� ��������� � config.h.dist  -skold

2004-02-12:
* ��������� ����������� � ������� ��������, ����� ��������� ����������
  ��������  -skold

2004-02-05:
* ����Σ� �������� VHOST ��� ������ ����������  -LoSt

2004-02-04:
* VHOST_MODE_MATCH ������ ����ޣ� ������  -skold

2004-02-03:
* ������� ���������� ������ �� �������� K/E � tkserv  -erra

2004-01-16:
* ���������� ������ � ������������� �������� DNSBL  -erra

2004-01-11:
* ����������� � expire_collision_map  -skold

2004-01-09:
* ���������� ������ ��������������� � add_history(pre_8) -skold
* ������ ���������������� ��������� �� ������ � m_umode -skold
* �������� KILL �������� �������� � expire_collision_map  -erra

2004-01-07:
* �������� ������� ����� � RPL_WHOISHOST  -erra
* ������ RPL_CHARSET ������ ֣���� ��������� ������ (� whois)  -erra
* � �������� ����������� �������� �������� ����� ������ ��������  -skold
* �������� ������ � ���������� invincible � ���������� SERVICES_SERV:
  �������� KILL ��� enforcer'�  -skold
* ������ � ������ �������������� ����� aCollmap->tstamp  -skold
* �������� ������������� � common/parse.c -skold

2004-01-06:
* ��������� ������� EXEMPT � tkserv (������ v1.4.0)  -erra
* �������� �������� ���������� TKSERV_VERBOSE  -erra
* �������� ��������� "TKLINE E ..." ��� �������������� � ���������  -erra
* �������� TK_MAXTIME ������ӣ� �� config.h � tkconf.h  -erra
* ֣���� ���������� �������� � tkserv �������� ���������� TK_MAXTIME  -erra

2004-01-05:
* ��������� ���������� ��� �������� �����, ���������� �� �������� -
  �� �� ������  -erra
* ����� ���� �������� #ifdef USE_SERVICES  -erra
* ����� �������� ����������� ����� �������� ������� ��������  -erra

2003-12-30:
* ���������������� ����� +h �����  -erra
* ����������� �������� ��������� ��������  -erra, skold
* m_restart - ��������� ��� ������ +x  -skold

2003-12-12:
* ���������� ������������ ������� :old NICK :new ��� �������� ����  -skold
* ���������� ��������� ���� � ����� ����  -skold
* ��������� �������� � m_quit  -skold
* ����� &LOCAL ������ ����� ������ �� ������������  -skold
* ����� �������� ������ ���� ������ ���������� � ����� � �������
  ���������  -skold

2003-12-09:
* �������� �������� MODES_RESTRICTED: ��������� /mode #channel +e/+I ���
  ���, ��� �� �� ������ (� �� �������� IRC)  -erra
* ����� �����ݣ� /mode #channel +I ��� ����, ����� ���������� ������
  (���  IRC)  -erra
* �������� ��� ��� ������ &LOCAL (��������� �� userlog)  -erra
* ����������������� ����������� ����� � config.h ��� ������ ����������  -erra

2003-11-30:
* ��������� ����� host/ip = ... and host/ip = !... � iauth.conf  -erra
* �������� "!" ��� ����� ���������� � ����� /stats A  -kmale
* ���������� �������� � ircdwatch.c  -erra
* ���������� ������� tolower/toupper � common/match.c.
  TODO: �������� ��� ��� �����  -erra

2003-11-28:
* ����� ޣ���� ������ EasyNet �� support/iauth.conf  -erra
* ����� �������������� ��ޣ� ��� ������� ���̣����� ������� � /lusers,
  ��������� ����� �������  -erra

2003-11-16:
* ����� �������� � get_client_xname (�������� ������)  -skold
* �������������� ������� � valloc � ������� ��������  -skold

2003-11-14:
* ��������� get_client_xname ��� m_trace  -erra
* ���������������� ��� ����������� #undef MACRO value, ����� ������
  �������������� gcc3.3  -erra

2003-11-08:
* ��������� ����� �� ������� �������� � m_service � m_nick  -skold
* ��������� ������ �� ��� anonymous, ������� �� ���� �� �������  -skold

2003-11-07:
* ���������� ������ ���������������, ��������� ��������� � opnotices  -skold
* ��������� m_trace, ����� �� ��������� ��������� ���� �������������
  � ������ +x  -skold

2003-11-04:
* ���������� �������� opnotice/opmsg ����� ���������  -kmale
* ��������� ����� ���������� � ������� ����� ���  -kmale
* �������� ����� ��������� IRC ��� ������� ����� ���  -erra
* ������������� ��������� ����� ��� �������� (S:)  -erra

2003-10-29:
* ��ޣ� � ���������� �������������  -erra
* ���������� �������� ��������������� ������, ��������� �����  -erra
* ��������� RPL_BOUNCE  -erra

2003-10-28:	[pre-release]
* ��������� ������ E: (���������� �� K:)  -erra
* ���������� ������ ������ � s_bsd.c (���������� ����)  -erra
* client_flood � localpref ��������������� � example.conf  -erra
* ������ E: ��������������� � example.conf  -erra
* ���������� ������ ��������������� ���������� ������ lock_nick �����
  exit_one_client  -erra
* �������� ��������� "KLINE *" ��� "KLINE *.domain" ��� m_kline  -erra

2003-10-27:
* ��������� ��������� RPL_ISUPPORT, ����Σ� ��� ������ RPL_BOUNCE  -erra
* ��������� ������������ ������������������ � channel.c  -erra
* �������� �������� client_flood (���������� ����) � ������ I: (�������
  � aconf->localpref)  -erra
* �������� ��� EXTRA_STATISTICS (�� IRCNet ircd)  -erra

2003-10-24:
* ��������� ������������� ��� localpref (� 0)  -erra
* ������ ������� ��������� ��������� �����  -erra
* �������� ������ ����� �� ������ ���� ��� ��������  -erra
* ��������� ������� strcpyzt (�������� �� strncpyzt)  -erra
* ����� �����������: ������� �� ��� �� ����, �� ������� ���ۣ� ������
  (B:)  -erra

2003-10-20:
* ������� �������� � mod_dnsbl (��������, ��� �����������) �� Beeth
* ���������� ��������� ������ "list = somehost.bl.org" (������ ���� ����)
  ��� mod_dnsbl  -erra

2003-10-18:
* ���������� ����������� ���������� ����� � ����� � ��������� �������  -erra

2003-10-13:	[Brain Damage]
* ������� ��������� ������ irc2.10.3p5 package, ����������� � ������������
  ������ � m_join buffer  -erra
* ���������� �������� �������� � config.h.dist (����������� � MAXLOCKS)  -erra

2003-10-12:
* ��������� ������ �� ������������ � �������� ���������� �����  -erra

2003-10-10:
* �������� �������� localpref � ����� ������� /stats c  -erra

2003-10-09:
* ���������� ������ ������ "ip = !1.2.3.4" �� iauth.conf  -erra
* ���������� ������ ������ "ip = ..." �� iauth.conf  -erra
* ��������� ��ޣ� "IP = ..." ��� ������ iauth -c iauth.conf  -erra

2003-10-07:
* ��������� ������������ � ������ �������� (��� �������� ����� ����)  -erra

2003-10-06:
* ��������� �������� �������� �������
  (���������� ��������� ��������: ircd/ircd_signal.c):
  - SIGCHLD ������������� �����������
  - s_restart() ����������� ���������� ��������� ��������
  - restart() ������� � ������ ���̣�
  - server_reboot() �� ���������� �������� ircd - ���������
  - #ifdef PROFIL � s_monitor �������� - �������  -skold
* ������ my[n]cmp �� common/match.c, ��� ������ �������� ��
  str[n]casecmp  -erra

2003-09-30:
* ���������� ������� ������ ��� ����� O: (�� ��������)  -erra
* �������� �������� ��� ��� /stats f  -erra

2003-09-29:	[Equinox+]
* ���������� ��������� ���������� "nick!"  -erra
* ���������� ����� ����������� ��������� ����� ������� � common/send.c  -erra
* ���������� ������� STATS ��� �� ���������� �� C/H/O/U, ����� �� �����
  O: �������� ��� �� ����������  -erra
* ��� ����� ��������� � config.h - VHOST_MODE_MATCH (�� ��������� ��������) �
  STATS_RESTRICTED (������� �� ���������)  -erra
* �������� ����� ����� X: �� F:  -erra
* ��������� ������� /stats f - �������� ������ F:  -erra
* ����� "���� ���������� IRC" ���������, ����� �������� ��������� ����  -skold

2003-09-28:
* ���������� ��������� ������ ��� �������  -skold
* �������� ����� ���������� IRC � ���, ��� �������� �������� +o  -skold
* �ݣ ���� ��������� �������� � ��������� ����������� ������  -erra
* ������� STATS ��������� ����, ����� ���������� ����  -skold
* �������� ��������� "nick!" ��� ��������� "nick +x" � ������
  ����������  -skold, -erra

2003-09-25:
* ����Σ� �������� ���������� ������  -erra

2003-09-25:
* �������� mod_webproxy.c (���� �� IRCNet ircd)  -erra
* ����Σ� mod_webproxy � ������������ � ����� ������  -erra
* doc/iauth.conf.5 � support/iauth.conf ��������� ��������������  -erra
* �������� ��������� ����� �� ������ rfc931  -erra
* �������� �������� NO_DIRECT_VHOST � support/config.h.dist � m_umode  -erra
* �������������� ����������� � support/Makefile.in

2003-09-24:
* ��������� � �������� ���������� ������, ���������� �������  -erra
* ��������� ����� 002  -erra
* ���������� ����� ���������� ������ "������� �� ������"  -erra
* ���������� ������� match_modeid ��� ����������� ������  -erra
* ����� ����������� ����� �� make_nick_user_host  -erra
* ������ ����� ������ ��� �� ����������� � ��������� �������� ��
  ������������ (opnotice)  -erra
* �������� ��������� ���� � ������ whowas  -erra

2003-09-23:
* ��������� ���������� ����������� (�����������) ������ ��� �����������������
  ������ +x  -erra
* ��������� ����� ������ � ������ ������ ����  -erra
* �������� �������� NO_DEFAULT_VHOST � config.h  -erra

2003-09-22:	[Equinox]
* ���������� ��������� ������� RMODE �� ��������� �������� ���������  -erra
* ��������� "connect thru" ���������� � ircd.conf (������ x:)  -erra
* ��������� chkconf.c ��� ����������� ����� X:  -erra
* ������ ������ ��� ������������� ������ ������������� (������ ���������
  IRC ����� ������ ��������� ���� �� /whois), ��������� ��� TODO  -erra
* ����Σ� ��� ������ "�������� ������� ��������"  -erra
* �������� ��������� ��� ������� � ������� b64, ����� ����� ���������������
  ���������� DNS  -erra
* �������� ������ �� ������������ ���������� � register_user  -erra

2003-09-19:
* �ݣ ����� ������� ������ �������� � can_join()  -erra
* �������� ��������� � m_invite() - ��������� ����������� ��
  �������������� �����  -kmale, -erra
* �������������� ������� ������ �������� �� ������������������, ��������
  ���������� �����  -skold

2003-09-18:
* ���������� "����������" ������ ��� ���������� ����, �������� �� �����,
  � ������ ���� ��� ��� ���� ���������� ��� �����������  -kmale, -erra

2003-09-14:
* ����� �������� � s_bsd.c (��� ��������)  -Umka
* ������� ������ ����������� ���������� ���������� � cptr->name,
  ��� � ��������� ������ ��� ���������������� ������� �������  -erra
* ������ ��������� ���� ��� ��������  -erra, -Umka

2003-09-13:
* ������� ����������� ������ ����������� �� iauth  -erra
* ��������� �������� � ������ mod_dnsbl.c � /stats a � iauth -c  -erra

2003-09-11:
* ����� �������� � mod_dnsbl.c, �������� �������� "paranoid"  -skold, -erra
* �����̣� doc/iauth.conf.5 �� ������ ��������� "paranoid"  -erra

2003-09-10:
* ��������� ������ ��������������� � mod_dnsbl.c  -erra
* ��������� ������� ��� ��������� �������� � shrink_collmap()  -erra
* ����� �������� � a_conf.c (iauth)  -erra
* ��������� ��������� ���� ������ � m_nick (s_user.c, ��������� ��������
  :old NICK :new)  -erra

2003-09-09:	[rc7]
* ���������� ������� �������� ������ �������� � common/parse.c  -erra
* ��������� ����� m_nick �� ��������� ��������  -erra

2003-09-08:
* ������ ��������� � �������� � ��������� �������� ����� ���� :old NICK :new
  ��� ��������  -erra

2003-09-07:
* �ݣ ������� �������� � ������� ��������  -erra
* ��������� ������ ��������������� � del_from_collision_map  -erra
* ����� �������� (FAQ)  -erra

2003-09-05:
* ��������� ������������ ������ ��������, ���������� ��������� ������  -erra
* ������� codepages-rusnet1.3/ ��� ����������  -erra

2003-09-02:
* �������� ircd/s_err.c � ircd/s_users.c �� ������� �������� �������
  ����� ������������ � ������ whois  -erra
* ������� ������ ��������  -erra

2003-09-01:
* ������� ���������������� ������� crc32+b64 (ircd/hash.c), ��������� ����
  ����������� ����� � ��������� aServer ��� ��������� �������� �����  -erra

2003-08-29:
* �������������� � ���������� ��������� �������� "NICK new", �������
  (�� �� ��������������) ��������� �������� ":old NICK :new"  -erra
  ���������� ��������, ����� ������ ��������.

2003-08-28:
* �������� ������� � m_force ����� �� �������� KILL � ��������
  �����������  -erra
* ������������� ������ rusnet/rusnet_cmds.c  -erra
* ���������� ������ ��������������� � ���������� ����� � tkserv  -skold
* �������� ������� m_nick � ����� ������������ ���������� �����,
  ������������  -erra

2003-08-27:
* ����� �������� � ircdwatch  -skold
* ����Σ� ������ DNSBL �� ��������� � support/iauth.conf  -erra
* ��������� �ݣ ���� ������ KILL �� FORCE � m_nick  -erra

2003-08-26:
* �������� ����� m_kill � m_force ��� ������ ��������, �������
  �� ������������ ��� �������  -erra

2003-08-25:
* ��������� support/iauth.conf: �������� ����� 'host' �� 'list' � ����������
  dnsbl  -erra

2003-08-05:
* ��������� �������� ��������� ����� - � config.h ������� �����
  ���������, ��������� � ���������� �����  -kmale
* ��������� ����� ����������� � ������ ���������������  -erra

2003-08-04:
* �����̣� iauth/a_conf.c, ����� ��������� ip = 1.2.3.4 ����� ���
  ip = 1.2.3.4/32 � iauth.conf  -erra

2003-08-01:
* ������� mod_dnsbl.c ��� iauth, ����� ��������� ��������� � ����������
  ޣ���� �������  -erra
* iauth.conf.5 �������� ����������� � dnsbl  -erra

2003-07-30:
* �������� ������ 'ip = ...' � ���������� �������� iauth.conf.5  -erra

2003-07-29:
* ���������� ��������� ������ ������� ��� ChanServ  -erra

2003-07-18:
* �������� ������� ������ &AUTH (� connlog)  -erra
* ��������� ������� ������� (� ����� � syslog)  -erra

2003-07-17:
* ���������� ������������� ���� ����� � �������� ������ ����� ������  -erra
* ��������� mod_dnsbl  -erra
* ��������� ������� ���� ������ &LOCAL  -erra

2003-07-16:	[rc6]
* �������� ������� ����� ��� ������� &ERRORS � &NOTICES � ����(�)
  (������������), ��� ����� ������ ��� ����� ���������� �� Makefile
  � config.h  -erra
* ����� ������ dnsbl ��� iauth  -erra

2003-07-15:
* �������� ��������� ������ /*serv, ����� ��� �������� PRIVMSG service@server
  ������ ������ PRIVMSG service  -erra

2003-07-11:
* ��������� support/Makefile.in ��� ������ chkconf  -erra

2003-07-09:
* ��������� �������� ������ �� ������������ � m_user  -LoSt
* ��������� ������ m_*serv ��� ������ /nickserv � �.�.  -erra
* ������������ ������ openconf() � dgets() ����������� � chkconf.c  -erra

2003-07-03:
* dgets() ��������� (common/support.c), ������ #include ���������
  ��������  -erra
* �������� ��� ������� &ERRORS (*.warn) � &NOTICES (*.info) � syslog  -erra

2003-07-01:	[rc5]
* ���������� ��������� opnotices/opmsg: �������, ��� �������� ircd ����������
  chptr->clist->flags � �������� ����������� �ޣ�����  -erra

2003-06-27:
* ���������� ���������������� ������� ���������� ��������� �����
  ���������. ���� ��� ����� � ircd,  ��� ���������� ��������� ������
  PASS ... |IRC, �� ��� ��� ���� ������� ������ ���� �� ���  -erra
* ������� ���� rusnet_proto �� ��������� Server - ��� ����������� ����������
  ���������� � ���� version  -erra

2003-06-19:
* return 0 �������� � ��������� ������ ������� � rusnet_cmds  -erra

2003-06-18:
* opnotice/opmsg ��������� � �������� ���������  -erra

2003-06-16:
* ��������� opnotice/opmsg (/notice @#channel, /msg @#channel)  -erra

2003-06-11:
* ���������� �������� ������� ����� �������� � tkserv  -erra

2003-06-06:
* ��������� ������� str[n]casecmp � common/support.c  -erra
* �������� ��������� � iauth.conf �� ������� ������ �������� ������  -erra
* �������� ����� strcasecmp � ������ configure � ���������  -erra

2003-06-05:	[rc4]
* ���������� ��������� ������� KLINE, ������ ��� ��������  -erra
* ����Σ� tkserv, ����� ��������� ��������� ��� ������� ������������
  ������ K:  -erra
* ����� ������ ������� ��� ��������� �����  -baron
* ����Σ� initconf(), ����� ��������� ��������� ������������  -erra
* �������� ������� � Makefile ��� tkserv, ����� �� ������� � kills.conf ������
  ircd.conf  -erra

2003-05-06:
* ��������������� ��������� ��� "����������" ����� K: � rusnet_cmds.c,
  �������� �������� TK_MAXTIME � config.h ��� ������ ���������  -erra

2003-05-05:	[rc3]
* �ݣ ��� ���������� ��������� ����� K: (������������ ����� �������� � ��������
  ���� ������������� ������� �� ������� /rehash, ���� �������������� ���� ����
  ������, ������������ � K:*:)  -erra
* ����� ������� ���������: KLINE -baron, -erra
* ������������� �������� � rusnet_cmds.c  -erra
* ����� ��������� � config.h ��� ��������� KLINE  -erra
* ������� RCPAGE ����� ���� ������� ����������, ���� ������ � config.h  -erra

2003-04-28:
* ������������ � ���������� ������ K: ��� �����. �������� ������� find_kill
  (�������� ����� ��������) ��� ����������� ��������� ����������������  -erra
* ������� �������� ����� ����, ��������� � ���������� ��������� "interface" �
  rusnet.conf  -erra

2003-04-26:	[rc2]
* ����� �����������: ��������� ������������ (������ c/C: - �������� localpref
  � ��������� Server), ����� ����� � ������� K:  -erra
* ���������������� ��������� "connect thru" � rusnet.conf ��������� ����������
  ������ (����� ������ �������������� IP, ����� ����������� �������� IP
  �������)  -erra
* ������� ��������� "interface" �� rusnet.conf ��� ����������  -erra
* �������������� rusnet.conf (��. doc/example.rusnet.conf)  -erra

2003-04-15:
* ���������� ������ � �������� ���������  -LoSt
* ����������� � m_force, m_rmode, m_rcpage  -erra
* ��������� ���������� (#ifdef RUSNET_IRCD) �� ������ ������ ����  -erra

2003-04-02:	[beta3]
* ����� ������� ���������: RMODE, RCPAGE  -baron
* ����� ����� ������: +c (�������������� ���������)  -baron
* ����������� � codepages.universal  -LoSt
* ��������� ircd/whowas.c  -LoSt
* ���������� common/parse.c � common/send.c  -LoSt
* ���������� configure � configure.in �� ������� ������� �����������
  Solaris �� FreeBSD 5.x  -erra

2002-09-22:	[beta1]
* rusnet/rusnet_cmds.c: �������� ��������� ������� FORCE � �����������������
  �� ����������� ����������������. ��� ������ ������������ ���������
  ������ �� ������ �������� ��������  -az

2002-09-21:	������
* RusNet IRCD ������ ������� �� ircd 2.10.3p3 (���� 2.10.3) � ftp.irc.org,
  ����������� ��� ����� ���� ���� ��������� #ifdef RUSNET_IRCD ��� ����������
  ������������� � ������ ������������  -erra


������ 1.4.1
_____________

PATCHLEVEL 5
------------

���������: rusnet/
		rusnet_init.c

	����� � �������� ��������, ����� �������� �� ������� � ���������
	"connect" ����� rusnet.conf ����� "thru 1.2.3.4", ��������
	������������ ��� ������� ������� �� ������ � rusnet.conf

	���������: �������.

PATCHLEVEL 4
------------

���������: rusnet/
		rusnet_cmds.c
	 
	������ �������� ������ ��� ��������� ������� FORCE � ����������
	������ (DEBUGMODE)  -Alex "Umka" Ljashkov

	 common/
		os.c (��.: RUSNET POLL)

	������� ��������� ��� ��������� ������� poll() � �� Linux.

PATCHLEVEL 3
------------

���������: rusnet/
		rusnet.h
		rusnet_init.h
		rusnet_misc.c
	 	rusnet_virtual.c
		s_bsd.c (��.: RUSNET CONNECT)

	� rusnet.conf ������� ���������, ����� ��������� ���������������
	��������� ���������� �� �������� ������ ��������� (����� IP)  -Adel


PATCHLEVEL 2
------------

2000-08-28:
* �������� WHOIS_NOTICES. ������ ��������� �������� ����� ��� �����������
  �� ����, ��������� �� ��� �� ������������� �������.

2000-08-25:
* ��������� EXTRA_NOTICES ��� ���������� ����. ������ �����, ������ ��� ������
  WHOIS �� ����. �������� JOIN/EXIT/NICKCHANGE �� ������ &OPER, ����� ��������
  ������������� � ������ +i (���������) � ������������� �� ������ �������,
  �� �������� �� ���. ��������� Makefile ��� ���������� codepages.

2000-08-17:
* ��������� ����� ������� ��� �����... ��� ���������� MacRoman 
  Big thanks: Alexander Javoronkov

2000-06-27:
* ��������� ��������� topic set by (��� 333)
