inherit ROOM;

void create()
{
	set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，街道上车
水马龙，人来人往，热闹非凡。南边是京城的交通要道东长安街。向北可以地安
门东大街。
LONG );
       set("exits", ([
		"north" : "/d/beijing/wang_7",
		"south" : "/d/beijing/wang_3",
		"east" : "/d/beijing/wang_6",
	]));

	set("coor/x", -10);
	set("coor/y", 290);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
	replace_program(ROOM);
}
