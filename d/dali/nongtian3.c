//Room: /d/dali/nongtian3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","农田");
        set("long", @LONG
这里已经是平原的尽头，对面就是险峻的山岭了，一些的农田和罗伽部村民
的房屋零星地分布在山脚下，一些村民正在田里耕作。有条道路向东南的山上蜿
蜒而去。
LONG );
	set("objects", ([
	   "/d/dali/npc/nongfu2": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"      : "/d/dali/nongtian2",
	    "southeast" : "/d/dali/shanlu7",
	]));
	setup();
	replace_program(ROOM);
}

