inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","»Ê¹¬±±ÃÅ");
        set("long", @LONG
ÕâÀï±ãÊÇ»Ê¹¬µÄ±±ÃÅ£¬ÕÉ¸ßµÄÖìºì´óÃÅ³¨¿ª×Å£¬ÃÅÉÏ½ğÉ«µÄÃ­¶¤ÉÁÉÁ·¢¹â¡£
´óÃÅÁ½ÅÔÕ¾×ÅÁ½ÅÅÉñÇéÑÏËàµÄÎÀ±ø£¬²»Í£µÄ´òÁ¿×Å¹ıÍùµÄĞĞÈË¡£²ÓÀÃµÄÑô¹âÖ±Éä
ÔÚÎ¡¶ëĞÛÎ°µÄ¹Å³ÇÇ½ÉÏ£¬Ê¹µÃ³ÇÇ½ÉÏ·½¡º×Ï½û³Ç¡»Èı¸öË¸½ğ´ó×ÖÏÔµÃ¸ñÍâµÄÒ«ÑÛ¡£
¶«³§ºÍÎ÷³§Á½¸ö¾©³ÇµÄÌØÎñ»ú¹¹¼ÜÉèÔÚ»Ê¹¬±±ÃÅµÄ×óÓÒÁ½²à¡£´Ó±±·½´©¹ıµØ°²ÃÅ
¿ÉÒÔµ½´ï±±¾©µÄ±±³Ç½¼¡£[2;37;0m
LONG );
	set("exits", ([
		"south" : "/d/beijing/hg",
		"north" : "/d/beijing/dianmen",
	]));
	set("objects", ([
		"/d/beijing/npc/bing2" : 1,
		"/d/beijing/npc/bing3" : 1,
		"/d/beijing/npc/yuqian1" : 1,
	]));
	set("no_fight", 0);
	set("coor/x", -30);
	set("coor/y", 300);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (objectp(ob = present("guan bing", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "ÉìÊÖÀ¹×¡ÄãÀÊÉùËµµÀ£º»Ê¹¬ÖØµØ£¬ÆñÈİÑ°³£°ÙĞÕ³öÈë¡£\n\n");
        if (objectp(ob = present("shi wei", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "ÉìÊÖÀ¹×¡ÄãÀÊÉùËµµÀ£º»Ê¹¬ÖØµØ£¬ÆñÈİÑ°³£°ÙĞÕ³öÈë¡£\n\n");
        return ::valid_leave(me, dir);
}
