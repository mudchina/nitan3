// liangong2.c

inherit ROOM;

void create()
{
	set("short", "练武场");
        set("long", @LONG
这里摆着一些铜人，他们比木人更加结实，也就不容易坏，因此也是高手修
炼上乘绝艺的地方。向南走穿过练功场就是王府内院。
LONG );
	set("exits", ([
		"south" : "/d/dali/liangong",
		"north" : "/d/dali/liangong3",
	]));
	set("objects", ([
                "/clone/npc/tong-ren": 4,
	]));
        setup();
	replace_program(ROOM);
}
