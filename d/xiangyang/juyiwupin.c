// Room: /d/xiangyang/juyiwupin.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "物品房");
        set("long", @LONG
这是聚义馆的堆放各种各样物品的房间。郭靖的二弟子武修文正在这儿负责
向有任务的新手分发各种物品。
LONG );
	set("exits", ([
		"northwest" : "/d/xiangyang/juyihuayuan",
	]));
	set("objects", ([
		"/d/xiangyang/npc/wuxiuwen" : 1,
	]));
	set("coor/x", -310);
	set("coor/y", -120);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

