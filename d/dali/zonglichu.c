//Room: /d/dali/zonglichu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","国务总理处");
        set("long", @LONG
总理处是镇南王皇太弟总理国务之处，满桌的奏章整理得井井有条。四周摆
了很多茶花，争奇斗艳。茶花是大理国花，看来主人对它也是钟爱有加。
LONG );
	set("objects", ([
	    "/d/dali/obj/shanchahua": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/sikong",
	    "south"  : "/d/dali/wfdating",
	    "east"   : "/d/dali/sima",
	    "west"   : "/d/dali/situ",
	]));
	setup();
	replace_program(ROOM);
}

