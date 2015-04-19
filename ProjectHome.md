The IRC protocol developed in early 1990s is still in use and even popular to some extent. Existing implementations lack of good iconv support which utf-ircd is intended to solve. Also features:
  * libidn support (international domain names are decoded to UTF-8)
  * SSL support
  * compressed server links (using Zlib)
  * cyrillic to latin translit (with libiconv 1.9.1 and later)
  * pure UTF-8 for server-to-server traffic
  * nick and channel names validation against chosen charset
  * number of non-standard user and channel modes