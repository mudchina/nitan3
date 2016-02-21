#include <room.h>
inherit ROOM;

void create()
{
	set("short", "杨柳胡同");
	set("long", @LONG
这里是杨柳胡同的深处。走到这里，光线越发的暗淡起来，狭窄的通道还在
不断的向南边延伸。
LONG );
       set("exits", ([
		"north" : "/d/beijing/yangliu1",
		"south" : "/d/beijing/yangliu3",
	]));

	set("outdoors", "beijing");
	set("coor/x", -60);
	set("coor/y", 240);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

