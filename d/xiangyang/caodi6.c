// Room: /d/xiangyang/caodi3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "草地");
        set("long", @LONG
这是襄阳城外的草地。蒙古兵进犯以来，这里的百姓全进城了，虽然蒙古兵
没来到南门，但肃杀氛围丝毫不减。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);
	set("exits", ([
		"north"  : "/d/xiangyang/southgate2",
		"south"  : "/d/wudang/wdroad5",
                "southwest"  : "/d/jingzhou/road1",
		"west"   : "/d/xiangyang/hunanroad1",
	]));
	set("coor/x", -290);
	set("coor/y", -150);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

