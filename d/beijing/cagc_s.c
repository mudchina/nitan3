#include <room.h>
inherit ROOM;

void create()
{
	set("short", "长安街广场");
        set("long", @LONG
这里便是长安街广场了，长安街广场是京城里最热闹、最杂乱的地段。南方
的一座天桥横跨东西，正是卖杂货、变把戏、跑江湖的闲杂人等聚居的所在。宽
阔的大道向南北两头延伸。从南方经过宏伟的凡陛桥就是北京城里的最有名的名
胜——天坛了，过天坛再向南方迈进就是永定门，通往郊外。在这里可以看见北
方不远处的一堵堵高大的城墙，那里便是天安门广场了。
LONG );
       set("exits", ([
		"south" : "/d/beijing/tianqiao",
		"north" : "/d/beijing/tiananmen",
	]));
	set("objects", ([
		"/d/beijing/npc/maiyi1" : 1,
		"/d/beijing/npc/xianren" : 2,
	]));
	set("outdoors", "beijing");
	set("coor/x", -30);
	set("coor/y", 250);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

