// Room: chufang.c
inherit ROOM;

void create()
{
	set("short", "厨房");
        set("long", @LONG
这是神龙岛的厨房，中央摆着大圆桌，周围则放着几张竹椅。神龙岛的弟子
都在这里用餐。
LONG );
	set("exits",([
	    "west" :__DIR__"zoulang",
            "east" :__DIR__"guoyuan",
	]));
	set("objects",([
		"/clone/food/jitui" : 3,
        __DIR__"obj/longxx.c" : 1,
		"/clone/food/jiudai" : 1,
        ]));

	set("resource/water", 1);
        set("no_fight", 1);
        setup();
	replace_program(ROOM);
}

