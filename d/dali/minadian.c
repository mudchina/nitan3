//Room: /d/dali/minadian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","蜜纳甸");
        set("long", @LONG
这里是乌夷分支乌蒙族阔部聚居的镇子，阔部领蜜纳甸和阔州。附近有溪流
汇入泸水，灌溉颇便利，因而农业相对谷中其他地区较发达。镇中尽是些简陋的
民居，也无甚客商过往。
LONG );
	set("objects", ([
	   "/d/dali/npc/shaonu": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"      : "/d/dali/gelucheng",
	    "southwest" : "/d/dali/zhenxiong",
	]));
	setup();
	replace_program(ROOM);
}

