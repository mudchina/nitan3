inherit ROOM;

void create()
{
	set("short", "全聚德酒楼二楼");
        set("long", @LONG
这里是雅座，文人学士经常在这里吟诗作画，富商土豪也在这里边吃喝边作
交易。这里也是城里举办喜宴的最佳场所。这里出售天下闻名的全聚德烤鸭。你
站在楼上眺望京城，只觉得心旷神怡。
LONG );
	set("exits", ([
		"down"   : "/d/beijing/quanjude",
	]));
	set("objects", ([
		"/d/beijing/npc/cheng" : 1,
	]));

	set("coor/x", 0);
	set("coor/y", 320);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
