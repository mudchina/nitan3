//Room: /d/dali/chahua6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","茶花园");
        set("long", @LONG
大理茶花冠绝天下，镇南王府的茶花自然更非凡品。你站在茶花园中，四周
是翠绿的灌木，环绕着的是碧玉般柔润的寒茵，一条清彻的小溪轻轻流下南面的
小湖，中间是一盆娇艳的茶花。
LONG );
	set("objects", ([
	   "/d/dali/obj/chahua5": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "south"  : "/d/dali/chahua3",
	    "north"  : "/d/dali/chahua7",
	]));
	setup();
	replace_program(ROOM);
}

