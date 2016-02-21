// Room: /d/xiangyang/caodi1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "草地");
	set("long", @LONG
这是荆州城外的草地。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
                "south"  : __DIR__"guandao3",
	]));
	set("objects", ([
                "/d/jingzhou/npc/obj/juhua" : 1,
	]));
	set("coor/x", -420);
	set("coor/y", -190);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

