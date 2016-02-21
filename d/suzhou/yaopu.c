// Room: /d/suzhou/yaopu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "立春堂");
        set("long", @LONG
这是一家药铺，一股浓浓的药味让你几欲窒息，那是从药柜上的几百个小抽
屉里散发出来的。药房先生却不在店内。一名小伙计站在柜台后招呼着顾客。
LONG );
//	set("no_clean_up", 0);
	set("exits", ([
		"south"  : "/d/suzhou/dongdajie2",
	]));
	set("objects", ([
		"/d/suzhou/npc/huoji" : 1,
	]));
	set("coor/x", 240);
	set("coor/y", -190);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

