// Room: /d/xiangyang/xiaorong2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "胡同");
        set("long", @LONG
这里是襄阳城内老百姓的居住区。只见小弄两边是有些小店面，有米行、小
杂货铺等。一些居民从这里进进出出。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"south" : "/d/xiangyang/jiekou2",
	]));
	set("objects", ([
		"/d/xiangyang/npc/boy"  : 1,
		"/d/xiangyang/npc/girl" : 1,
	]));
	set("coor/x", -270);
	set("coor/y", -50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

