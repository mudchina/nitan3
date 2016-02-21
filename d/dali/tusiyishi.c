//Room: /d/dali/tusiyishi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","议事厅");
        set("long", @LONG
议事厅中央有神龛，龛下陈列着刀、叉、矛、戟等兵器。宽阔的大楼上下，
柱梁粗实。厅堂宽敞，前后各有一长排坐栏，供人纳凉憩息。
LONG );
	set("objects", ([
	   "/d/dali/npc/datusi": 1,
	   "/d/dali/npc/zutouren": 2,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "down"  : "/d/dali/tusimentang",
	]));
	setup();
	replace_program(ROOM);
}

