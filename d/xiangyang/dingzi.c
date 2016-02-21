// Room: /d/xiangyang/dingzi.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "丁字街口");
        set("long", @LONG
这里是襄阳城北部的丁字街口。向北一直通向玄武门，东面和西面是一条笔
直的青石大街，通向城内。南面是一堵上盖红色琉璃瓦的高墙，里面是襄阳安抚
使吕文德的府邸。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : "/d/xiangyang/northroad2",
		"west"  : "/d/xiangyang/northroad1",
		"north" : "/d/xiangyang/northjie",
	]));
	set("coor/x", -300);
	set("coor/y", -50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

