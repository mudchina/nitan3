inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","海澄公府大院");
        set("long", @LONG
这是进门后的一个不大的花园。西面是一个厢房，东面是一扇月形门通往海
澄公府的花厅，北面是海澄公府的大门，南面就是大厅了。
LONG );
	set("exits", ([
		"north" : "/d/beijing/hai_men",
		"south" : "/d/beijing/hai_dating",
		"east" : "/d/beijing/hai_huating",
		"west" : "/d/beijing/hai_fang",
	]));
	set("objects", ([
		"/d/beijing/npc/yuqian1" : 1,
		"/d/beijing/npc/yuqian2" : 1,
	]));

	set("coor/x", 20);
	set("coor/y", 300);
	set("coor/z", 0);
	setup();
}