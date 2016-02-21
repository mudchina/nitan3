//Room: /d/dali/dalinorth.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","大理城北");
        set("long", @LONG
这里是个岔路口。南边就是大理城的北门了，道路从这里分岔，北去可到太
和城，西北通向下关城，也通苍山，是去游苍山和崇圣寺的必经之路。
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"      : "/d/dali/taihecheng",
	    "south"      : "/d/dali/northgate",
	    "northwest"  : "/d/dali/ershuiqiao",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

