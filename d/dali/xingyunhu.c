//Room: /d/dali/xingyunhu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","星云湖畔");
        set("long", @LONG
星云湖又名小镜湖，方圆有十数里。东靠玉霞山，碧水清澈，风光妩媚，乃
是大理东部名景。明月之夜，皎洁的月光映照湖面，风拂水波，摇曳生姿，如繁
星落入湖中，晶亮如云，故名之。在此远眺湖之东南岸，可见青青翠竹，似有房
舍隐在其中。
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"    : "/d/dali/buxiongbu",
	    "eastup"   : "/d/dali/yuxiashan",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

