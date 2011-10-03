!! Всегда сверяйтесь с английской версией этого документа!   !!
!! Русский текст может быть устаревшим или неполным.         !!

Задаваемые вопросы и возможные ответы.
--------------------------------------------------------
2.x СПРАВОЧНИК ПО RUSNET-IRC
=======================================================================
1. Расширенный синтаксис для банов и строк K/R/E
   Начиная с версии 2.0, ircd поддерживает шаблоны наборов символов ([a-z]),
   если шабло начинается с символа &. Таким образом новая функциональность
   не затрагивает старые строки.

2. Поддержка доменных имён на национальных языках (IDN). Важным следствием
   из этого является то, что теперь ircd.conf (и особенно kills.conf) должен
   храниться строго в кодировке UTF8.

3. Спам-триггеры (команды /trigger и /untrigger) для сообщений, отправленных
   локальными клиентами. Хранятся в ircd.conf (kills.conf) как строки T:, для
   обновления используется /rehash t, для контроля /stats T. Из сообщений
   перед проверкой на спам вырезаются цвета, если в config.h определено
   STRIP_COLORS (по умолчанию).

4. Режимы пользователя +c (не принимает цветные сообщения), +I (идентифицирован
   сервисами) и +R (принимает сообщения только от идентифицированных ников).
   Режим канала +R (разрешает вход только идентифицированным пользователям).


1.5.x СПРАВОЧНИК ПО RUSNET-IRC
=======================================================================

1. Расширение поддержки кодировок
   Версия 1.5.0 имеет возможность поддерживать любые задаваемые клиентом
   кодировки. Для включения этой возможности в ОС, где собирается ircd,
   должна быть установлена libiconv (внимание: большинство, если не все
   версии libiconv не имеют поддержки транслита кириллицы, для FreeBSD
   патч к libiconv см. в каталоге contrib дерева исходников). При запуске
   configure нужно вводить ещё один дополнительный параметр --enable-iconv
   и внимательно смотреть на то, что он пишет. Если получите сообщение о
   том, что ваш iconv не поддерживает кириллический транслит, то это как
   раз и означает, что вам придётся пересобирать libiconv для того, чтобы
   поддержка транслита кириллицы в нём появилась. Также обратите особое
   внимание на то, что в вашей системе обязательно должна присутствовать
   локаль LOCALE.CHARSET_8BIT (в случае RusNet - uk_UA.KOI8-U)! И если вы
   хотите иметь внутреннюю кодировку UTF-8 для полной поддержки юникода
   для клиентов, то может потребоваться наличие LOCALE.CHARSET_UNICODE
   (для RusNet - uk_UA.UTF-8). Проверьте их наличие перед тем, как будете
   продолжать далее.
   При включении поддержки iconv отпадает необходимость в установке как
   rusnet.conf, так и каталога codepages, не паникуйте, не обнаружив их
   после установки.
   Конфигурирование перед сборкой:
   1. Константы в config.h:
      LOCALE* и CHARSET* -- НЕ МЕНЯТЬ! Глобальные настройки сети (RusNet).
      IRCD_CHANGE_LOCALE - меняет способ преобразования строк к верхнему
		регистру, при внутренней кодировке UTF-8 и наличии в
		системе локали uk_UA.UTF-8 может положительно сказаться на
		производительности, поэтому определено. Если обнаружатся
		проблемы с системными библиотеками в такой локали, можно
		попробовать убрать.
      DO_TEXT_REPLACE - если определено, то каждый не преобразуемый в
		текущую кодировку клиента символ будет преобразован в
		символ, задаваемый TEXT_REPLACE_CHAR. В противном случае
		такие символы будут просто пропускаться при отправке
		клиенту.
   Настройка после установки:
   1. Строки P: в ircd.conf имеют новое поле, которое раньше было пустым.
      Теперь это поле обязательно к заполнению - там должна быть указана
      кодировка по умолчанию для клиентов, которые приходят на этот
      порт. Строки P: (и p:), в которых не указана или указана неверная
      (несуществующая) кодировка, игнорируются.
      Примеры строк P:
	P::koi8-u::6667:
	P::ascii::6668:
	P::cp1251::6669:
	P::cp866::7772:
	P::iso-8859-5::7773:
	P::MacCyrillic::7774:
   2. Порт в строке M: в ircd.conf в последнем поле несёт дополнительное
      значение - строка P: с соответствующим портом в поле кодировки
      должна иметь ту кодировку, которая будет использоваться ircd для
      хранения данных в памяти (внутренняя кодировка). Соответственно:
	- ни один клиент не сможет общаться с кем-либо, используя символы,
	  не входящие в эту кодировку, поэтому эта кодировка должна иметь,
	  как минимум, все символы, входящие в CHARSET_8BIT - для сети
	  RusNet это могут быть koi8-u, cp1251, utf-8;
	- все логи (а также файл kills.conf!) будут записываться в этой
	  кодировке;
	- максимальная производительность ircd будет достигаться, когда
	  большинство соединений будет в этой же кодировке.
      Внимание: при установке внутренней кодировки в utf-8 сервер будет
      иметь максимальную поддержку всего набора символов юникода, в т.ч.
      всех известных кодировок, но есть опасность образовать более, чем
      один юникодный сегмент в сети, что неминуемо вызовет жалобы от
      клиентов, поэтому делать это без согласования с координаторами
      сети категорически не рекомендуется!
   3. Внутренняя кодировка может меняться "на лету" по команде /rehash
      или по сигналу -HUP, но если её поменять на несовместимую с набором
      CHARSET_8BIT кодировку - последствия могут быть непредсказуемыми,
      поэтому менять её таким образом на сервере, находящемся в составе
      сети, категорически запрещается.
   4. Кодировка ircd.conf и ircd.motd может задаваться при старте ircd
      при помощи ключа командной строки -e. По умолчанию она совпадает с
      CHARSET_8BIT. В процессе работы меняться не может.
   5. По команде /stats e можно посмотреть статистику по использованию
      кодировок. Каждый слушающий порт, каждый подключенный сервер или
      клиент добавляет 1 к соответствующей строке. Внутренняя кодировка
      также представлена в списке и также добавляет 1.

   Устанавливать внутреннюю кодировку koi8-u и при этом собирать сервер с
   поддержкой iconv также имеет смысл по следующим причинам:
     - некоторое увеличение производительности за счёт изменений в
       алгоритме хранения/поиска ников/каналов;
     - "более правильный" транслит.

   Команда CODEPAGE заменена на CHARSET. Команда CODEPAGE поддерживается
   в порядке обратной совместимости.

2. Поддержка IPv6.

    Лучше всего, если вы прямо укажете, хотите или нет использовать IPv6,
    путём указания либо --disable-ipv6, либо --enable-ipv6 в строке вызова
    configure. Если вы выбираете включить поддержку IPv6, то вам придётся
    заменить все разделители в файле ircd.conf - вместо символа ':' они
    теперь будут '%', потому что символ ':' используется в записи адресов
    IPv6. Будьте внимательны и не пропустите этот момент! Кроме того,
    скорее всего, понадобится включить поддержку виртуальных адресов для\
    IPv6 параметром --enable-vhost6

1.4.3 СПРАВОЧНИК ПО RUSNET-IRC
=======================================================================

1. Описание пользовательского режима +b
   Не разрешены: 
	- изменение NICKа
	- PRIVMSG/NOTICE пользователям за исключением операторов и
	  сервисов IRC
	- PRIVMSG/NOTICE более чем одному нику одновременно или в #канал
	- собственные сообщения QUIT/PART (signoff/leave)
	- AWAY, VERSION, INFO, LINKS, TRACE, STATS, HELP, LUSERS, MOTD
	- UMODE -b и UMODE +x
	- получение +o/+v на каналах, команда MODE
	- JOIN на несколько каналов одновременно
	- JOIN на каналы &/!
   Штрафное время (penalty) за каждую попытку запрещенной команды, 
   увеличены пенальти за выполнение ADMIN, TIME и JOIN.
   Лимит клонирования для +b пользователей не зависит от строк I: и равен 2.

2. Специфическая для RusNet конфигурация: строки R:
   Строки RusNet R: синтаксически идентичны строкам K:, но вместо
   отключения клиента они применяют пользовательский режим +b к клиенту.
   Заметим, что клиент строки R: будет иметь первым символом идент-строки
   %, так что его легко можно забанить на каналах или найти посредством
   WHO %*. Можно записывать причины в строках R: точно так же, как и
   в строках K:. Эта причина будет показана клиенту при соединении
   непосредственно перед специальным сокращённым MOTD.
   Строки R: являются сугубо предпочтительным способом обращения со
   спаммерами, хулиганами и флудерами, которые являются живыми людьми.
   Строки R: позволяют клиенту соединение с сервером и вход на каналы,
   но делают хулиганство практически невозможным и не вызывают при
   этом kill/connect флуда от этих клиентов.
   Для троянцев/спамботов строки K: по-прежнему являются лучшим решением,
   но можно также использовать R: и для них, особенно если сервер несёт
   большую нагрузку из-за повторных соединений этих троянцев, - всё равно
   из присутствие на каналах вряд ли сможет кому-нибудь повредить.
    
3. Возможности SSL
   Чтобы добиться работоспособного SSL, Вам нужно иметь установленные
   библиотеки OpenSSL. Запустите configure и убедитесь, что он нашёл
   заголовки и библиотеки, укажите пути к ним в параметрах, если OpenSSL
   установлен в нестандартное место и не обнаружен configure.
   Запустите скрипт support/ssl_cert и ответьте на все заданные им
   вопросы - местонахождение сервера, имя сервера, и так далее. Учтите,
   имя сервера (hostname) должно быть тем, которое используют пользователи
   при соединении. Скрипт создаст файлы ircd.crt и ircd,key. Поместите
   их в каталог конфигурации ircd (обычно etc/). В файле config.h никаких
   изменений не потребуется.
   Добавьте в файл ircd.conf строки:
   p::::9997:
   p::::9998:
   p::::9999:
   
   Добавьте также в rusnet.conf:
   codepage none port 9997;
   codepage translit incoming TRN2UNI outgoing UNI2TRN port 9998;
   codepage cp1251 incoming WIN2UNI outgoing UNI2WIN port 9999;
   
4. Команда rehash
   Функция rehash была полностью переработана в этой версии, поскольку
   предыдущая напрасно потребляла процессор и содержала ошибки. Теперь
   при изменении одной строки в ircd.conf нет нужды перечитывать всё,
   вместо этого можно указать дополнительный параметр команде REHASH и
   перечитать только часть. 
   Доступные параметры:
   /rehash b    [будут перечитаны строки переназначений B:]
   /rehash c    [будут перечитаны строки C: и Y:]
   /rehash dns  [будет сброшен кэш DNS и перечитан /etc/resolv.conf]
   /rehash e    [будут перечитаны строки E: (исключения из K:)]
   /rehash h    [будут перечитаны строки H:, C: и Y:]
   /rehash i    [будут перечитаны строки I: и Y:]
   /rehash k    [будут перечитаны строки K:]
   /rehash l    [будут перечитаны строки L:, C: и Y:]
   /rehash motd [будет перечитан MOTD сервера]
   /rehash o    [будут перечитаны строки O: и Y:]
   /rehash p    [будут перечитаны строки P: и p:]
   /rehash r    [будут перечитаны строки R: (режим +b RusNet)]
   /rehash ssl  [будут перечитаны строки p: и перезапущен SSL]
   /rehash y    [будут перечитаны строки Y:]
   /rehash      [будет перечитан весь файл]
   kill -HUP эквивалентен команде /rehash без параметров.
   
5. Новый синтаксис строк K/R/E и как менять их динамически.

   Эта версия rusnet-ircd предоставляет новый простой способ добавлять
   строки K/R/E оператору сервера.
   Синтаксис команд:
   KLINE <nick!user@host> <продолжительность> [:причина]
   UNKLINE <nick!user@host>
   
   команды ELINE и RLINE имеют точно такой же синтаксис. Если причина
   не указана, в строку будет записано "No reason".
 
   Любой оператор может использовать эти команды для работы со строками
   K/R/E на своём сервере, вместо того чтобы редактировать вручную файл
   конфигурации.
 
   (!) Не нужно выполнять REHASH, поскольку эти команды действуют
   немедленно.
   (!) Заметьте, новый синтаксис позволяет маски любого вида, в которые
   можно включать и маску ника, и маску ident одновременно.

   Строки можно просматривать командами:
   STATS k
   STATS e
   STATS r
 
   Возьмите на заметку следующие простые правила:

   Для строк K: и R:
   1. Если задать строку с маской более узкой, чем уже существующая, и
      сроком действия более коротким, чем в существующей строке, новая
      строка не будет добавлена.
   2. Если добавлять строку с маской более широкой, чем уже имеющиеся, и
      срок действия будет больше, все имеющеся строки, подпадающие под эти
      условия, будут удалены, и добавится новая строка.
   3. Аналогичная логика применяется при задании маски на удаление.

   Для строк E:
   1. Строки E: теперь тоже имеют срок действия и причину. Не забывайте
      об этом.
   2. Вне зависимости от того, является ли добавляемая маска более строгой 
      или менее, чем уже  существующая, старая маска будет заменена новой.
      
6. Что мы теперь используем вместо TkServ?
   Как упоминалось в RELEASE_NOTES, в rusnet-ircd, начиная с 1.4.3p8, нет
   TkServ'а, ircd использует встроенный модуль iserv для работы с динамическими
   строками.

   НЕ НУЖНЫ:
   -------------
   Строка S: в ircd.conf.
   Любая дополнительная конфигурация до и после сборки.
   Любые дополнительные пароли.
   Любые дополнительные команды make/make install.
   
   НУЖНЫ:
   -------------
   #include kills.conf 
   
   в файле ircd.conf, А ТАКЖЕ
   (!) право на создание/удаление файлов в конфигурационном каталоге (обычно etc/) 
       для пользователя ircd. 
 
 
1.4.2 СПРАВОЧНИК ПО RUSNET-IRC
=======================================================================

1. Как организовать автосоединение? Почему могут случиться автосоединения
не к тем серверам? Почему вообще нет автосоединения?

   Уделите тщательнейшее внимание классам соединений. Все соединения
   с вышестоящими серверами ОБЯЗАНЫ быть в одном классе, и в этом классе
   ОБЯЗАТЕЛЬНО должен быть установлен максимум соединений в 1.
   Все соединения с нижестоящими серверами ОБЯЗАНЫ НЕ попадать в этот
   класс, но в какой-нибудь другой.  Автосоединения с нижестоящими
   серверами быть не должно за исключением особых случаев.

   ЗАМЕТЬТЕ: если используется любой сервис наподобие tkserv (строка S:),
   он ОБЯЗАН НЕ попадать в класс вышестоящих серверов, иначе максимум
   соединений будет исчерпан, и автосоединение работать перестанет.

2. Приоритеты автосоединений.
   Если один из вышестоящих серверов явно лучше другого, можно назначить
   ему больший приоритет, так что Ваш сервер будет инициировать соединение
   с ним чаще.
   Пропишите административное предпочтение (следующий параметр за номером
   класса) в строке c/C:. Чем выше число, тем больше предпочтение.
   Синтаксис:
   c:<Адрес IP>:<пароль>:<имя сервера>:<порт>:<класс>:<приоритет>
   ПРИМЕЧАНИЕ: эта возможность есть только в RusNet IRCd.

3. Дополнения к K:line
   Можно поставить K: не только по пользователю/хосту, но и по нику/хосту.
   Учтите, что нельзя поставить K: на пару ник/пользователь, поскольку
   ник сверяется по полю ident строки K:. В частности, это означает, что
   K: на ник будет срабатывать на такой же ident, и наоборот.
   И ЕЩЁ РАЗ: нельзя указать ник и ident пользователя в одной строке K:
   ПРИМЕЧАНИЕ: и эта возможность есть только в RusNet IRCd.

4. В чём разница между командой /quote RESTART и рестартом сервера
   посредством отстрела процесса ircd?
   В этой версии команда RESTART исправлена и работает гибко.
   /quote RESTART сбрасывает все буферы отправки и закрывает все соединения,
   как и отстрел процесса (в том числе сигналом SIGINT). Но команда RESTART
   производит execv и перезапуск себя (не внешними средствами), сохраняя тот
   же PPID, но загружая при этом новый код с диска. Команда RESTART работает
   намного быстрее, чем простой рестарт.

5. Проблемы с DNS, имена хостов некоторых клиентов не резолвятся.
   В config.h появился параметр RESTRICT_HOSTNAMES. Он требует строгого
   соответствия имени хоста RFC 1123. Если, например, у вашего провайдера
   много типичных ошибок DNS, таких как подчеркивание "_", имя хоста не 
   будет резолвиться. Если исправить эти ошибки невозможно, жизнь клиентам с
   подчерками в именах хостов можно упростить, задав в config.h параметр
   HOSTNAMES_UNDERSCORE.

6. Специальные настройки для активных игровых роботов, которые посылают много
   сообщений, и их из-за этого отключает.
   RusNet ircd использует дополнительное поле в строках i/I: персональное
   значение client_flood (в байтах). Чем больше значение, тем больше буфер
   выделяется.

   Синтаксис:
   I:<Адрес IP>:<пароль>:<имя хоста>:<порт>:<класс>:<Client_Flood>

7. Специальная возможность для серверов с несколькими адресами IP и различными
   правилами маршрутизации для них: строки F:, которые позволяют установить
   соединение с другим сервером, используя адрес IP, отличный от основного
   адреса интерфейса либо адреса, указанного в строке M: конфигурации сервера.

   Синтаксис: F:<Target IP>:<link description>:<IP to bind>:

   Если запрошенный адрес IP <IP to bind> недоступен, соединение будет
   устанавливаться с основого адреса IP. В поле <target IP> записывается
   адрес IP сервера, с которым осуществляется соединение.

   В текущей версии можно указывать только адреса IP, но не имена DNS.
