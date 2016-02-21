inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",RED"¶«³§"NOR);
        set("long", @LONG
ÕâÀï¾ÍÊÇ¾©³ÇµÄÌØÎñ»ú¹¹¡ª¡ª¶«³§¡£´óÌüÄÚºÜÊÇ¿íÀ«£¬ÕâÀï¾¯±¸ÉîÑÏ£¬´©×Å
ÖÆ·şµÄ¶«³§¹Ù±øºÍÌ«¼àÔÚÕâÀïÀ´»Ø×ß¶¯¡£¿´À´ÕâÀï²»ÒË¾ÃÁô£¬¸Ï¿ìÀë¿ªÎªÃî¡£[2;37;0m
LONG );
	set("exits", ([
		"north" : "/d/beijing/dongchang_men",
	]));
	set("objects", ([
		"/d/beijing/npc/bing2" : 4,
		"/d/beijing/npc/taijian" : 1,
	]));
	set("no_fight", 0);
	setup();
}
