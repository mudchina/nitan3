//Room: /d/dali/cangshanzhong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","苍山中部");
        set("long", @LONG
你行走在苍山中部山颠，此间地形极险，两边山高入云，中间一条崎岖不平
的山路。路西不远一条大河自北略偏西方向南流过，隆隆水声遥遥可闻，正是南
诏名川--泸水。此路是自西川和土番入大理的必经之途，时有客商过往。由此向
南穿越苍山可抵下关城，北面不远则是出苍山的山口。
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"      : "/d/dali/jianchuan",
	    "southwest"  : "/d/dali/cangshanlu1",
	    "southeast"  : "/d/dali/xiaguan",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

