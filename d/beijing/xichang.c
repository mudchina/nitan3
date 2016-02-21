inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",RED"Î÷³§"NOR);
        set("long", @LONG
ÕâÀï¾ÍÊÇ¾©³ÇµÄÌØÎñ»ú¹¹¡ª¡ªÎ÷³§¡£´óÌüÄÚºÜÊÇ¿íÀ«£¬ÕâÀï¾¯±¸ÉîÑÏ£¬´©×Å
ÖÆ·şµÄÎ÷³§¹Ù±øºÍÌ«¼àÔÚÕâÀïÀ´»Ø×ß¶¯¡£¿´À´ÕâÀï²»ÒË¾ÃÁô£¬¸Ï¿ìÀë¿ªÎªÃî¡£[2;37;0m
LONG );
	set("exits", ([
		"north" : "/d/beijing/xichang_men",
	]));
	set("objects", ([
		"/d/beijing/npc/bing3" : 4,
		"/d/beijing/npc/taijian" : 1,
	]));
	set("no_fight", 0);
	set("coor/x", -40);
	set("coor/y", 280);
	set("coor/z", 0);
	setup();
}