inherit ROOM;

void create()
{
	set("short", "大官道");
	set("long", @LONG
这是一条宽阔笔直，尘土飞扬的大官道，足可容得下十马并驰。南边
是东都洛阳古城，往北直上可以到达华山。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : "/d/kaifeng/ximen",
  		"south" : __DIR__"guandaon3",
	]));

	set("coor/x", -170);
	set("coor/y", 100);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
