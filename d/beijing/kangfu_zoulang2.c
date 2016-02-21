#include <room.h>
inherit ROOM;

void create()
{
	set("short", "康府走廊");
        set("long", @LONG
这是一条木制的走廊，地面很是光滑，被打整得一尘不染。几个康府的下人
在此走动。南边是康府的大厅，左右两侧是两个厢房。北边是康亲王的书房所在。
这里站着一个秃头和尚，那是康府的侍卫头领。
LONG );
       set("exits", ([
		"north" : "/d/beijing/kangfu_shufang",
		"south" : "/d/beijing/kangfu_dating",
		"west" : "/d/beijing/kangfu_xifang",
		"east" : "/d/beijing/kangfu_dongfang",
	]));
	set("objects", ([
		"/d/beijing/npc/jiading_k" : 1,
		"/d/beijing/npc/yahuan_k" : 1,
		"/d/beijing/npc/shenzhao" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x", -30);
	set("coor/y", 310);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}