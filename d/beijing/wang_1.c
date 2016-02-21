inherit ROOM;

void create()
{
	set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，街道上车
水马龙，人来人往，热闹非凡。南边是京城的交通要道东长安街。西边是一座富
丽堂皇的建筑，那是当朝皇上的第一宠臣——韦公爷的府邸。东边不远是京城的
刑场，是朝廷处决钦犯的场所。
LONG );
       set("exits", ([
		"north" : "/d/beijing/wang_3",
		"south" : "/d/beijing/caroad_e1",
		"east" : "/d/beijing/wang_2",
		"west" : "/d/beijing/weifu_men",
	]));
	set("objects", ([
		"/d/beijing/npc/youren" : 1,
	]));

	set("coor/x", -10);
	set("coor/y", 270);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
	replace_program(ROOM);
}

