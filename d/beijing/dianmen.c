#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"µØ°²ÃÅ¹ã³¡"NOR);
        set("long", @LONG
ÕâÀï¾ÍÊÇµØ°²ÃÅ¹ã³¡£¬»ÒÉ«µÄ³ÇÇ½¸øÈËÒÔ×¯ÑÏËàÄÂÖ®¸Ğ£¬Íù±±Í¨¹ı×Ï½û³ÇµÄ
µØ°²ÃÅ¾ÍÊÇ³Ç½¼ÁË¡£Ô¶Ô¶ÍûÈ¥£¬×Ï½û³ÇµÄÂÖÀªÒæ·¢ÏÔµÃĞÛÎ°¸ß´ó£¬Ò»Ìõ»¤³ÇºÓÈÆ
³Ç¶ø¹ı¡£Ò»Ìõ±ÊÖ±µÄÇàÊ¯´óµÀºá¹á¶«Î÷£¬¶«±ßÊÇµØ°²ÃÅ¶«½Ö¹ã³¡£¬Î÷±ßÊÇµØ°²ÃÅ
Î÷½Ö¹ã³¡¡£ÄÏ±ßÍ¨¹ıÒ»ÌõĞ¡ÇÅ¾ÍÊÇ»Ê¹¬µÄ±±ÃÅÁË¡£[2;37;0m
LONG );
	set("exits", ([
		"south" : "/d/beijing/hgmen_n",
		"north" : "/d/beijing/di_dajie1",
	       "west" : "/d/beijing/di_xigc",
              "east" : "/d/beijing/di_donggc",
	]));
	set("objects", ([
		"/d/beijing/npc/bing1" : 2,
		"/d/beijing/npc/bing3" : 1,
		"/d/beijing/npc/old2" : 1,
		"/d/beijing/npc/kid1" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x", -30);
	set("coor/y", 310);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
