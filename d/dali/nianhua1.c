//Room: /d/dali/nianhua1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","拈花寺后院");
        set("long", @LONG
你举步入寺，只听得叮叮两声清磬，悠悠从后院传出，霎时之间，只感遍体
清凉，意静神闲。你踏实着寺院中落叶，走进后院。你站在庭中，眼见庭中一株
公孙树上一片黄叶缓缓飞落，俗念全消。
LONG );
	set("objects", ([
//	   "/d/dali/npc/huangmei": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "out"  : "/d/dali/nianhuasi",
	]));
	setup();
	replace_program(ROOM);
}

