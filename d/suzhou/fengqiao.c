// Room: /d/suzhou/fengqiao.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "枫桥");
        set("long", @LONG
寺的北面有一座桥孔呈半圆的单空石桥--枫桥，她跨于运河的枫桥湾。桥的
东面是铁岭关，它与白虎关，浒墅关，合称苏州三关。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"enter" : "/d/suzhou/hanshidian",
		"north" : "/d/suzhou/tielingguan",
	]));
	set("coor/x", 140);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

