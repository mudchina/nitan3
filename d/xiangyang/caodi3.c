// Room: /d/xiangyang/caodi3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "草地");
        set("long", @LONG
这是襄阳城外的草地。蒙古兵进犯以来，这里的百姓全进城了，蒙古兵驰骋
来去，以为牧场，尘土飞扬，甚是嚣张。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"south"  : "/d/xiangyang/northgate2",
                "north"  : "/d/changan/hanguguan",
                "northeast"  : "/d/luoyang/guandaos6",
	]));
	set("objects", ([
		"/d/xiangyang/npc/menggubing" : 2,
	]));
	set("coor/x", -300);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

