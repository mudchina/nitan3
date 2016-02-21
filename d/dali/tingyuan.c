//Room: /d/dali/tingyuan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","庭院");
        set("long", @LONG
这里是镇南王府的庭院，中间一个小水潭，边上种着许多不知名的花，几只
喜鹊在花丛中蹦来跳去，花丛边有片小竹林，竹影下放着石桌石凳，经常有人在
这下棋。
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"  : "/d/dali/shijing",
	    "east"  : "/d/dali/chahua1",
	    "north" : "/d/dali/changlang",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
