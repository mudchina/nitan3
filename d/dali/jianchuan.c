//Room: /d/dali/jianchuan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","剑川镇");
        set("long", @LONG
这里是剑川的镇中心，镇子不大，居民绝大部分是乌夷族，几乎全都以狩猎
为生。由于山高地寒，附近山林的野兽大多皮粗毛厚，有不少皮货商在这里和当
地猎人交易。北出山口则属大理北疆，也是入蜀之途，南穿苍山则可抵大理内陆。
LONG );
	set("objects", ([
	   "/d/dali/npc/lieren": 1,
	   "/d/dali/npc/pihuoshang": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"      : "/d/dali/jianchuankou",
	    "south"      : "/d/dali/cangshanzhong",
	]));
	setup();
	replace_program(ROOM);
}

