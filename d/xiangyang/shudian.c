// Room: /d/xiangyang/shudian.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "书店");
        set("long", @LONG
这里的老板刚从南阳搬来，听说以前他曾在嵩山少林寺出过家，后不知什么
原因又还了俗，专门卖书为生。只见书店面积很大，以前曾是一座勾栏。
LONG );
	set("exits", ([
		"east" : "/d/xiangyang/westroad2",
	]));
	set("objects", ([
		"/d/xiangyang/npc/shudianboss" : 1,
	]));
	set("coor/x", -330);
	set("coor/y", -60);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
