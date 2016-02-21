//Room: /d/dali/zhulou3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","大竹楼");
        set("long", @LONG
这是一座普通样式的台夷竹楼，建在鲁望镇中心，与四周其它竹楼比占地广
大得多，也特别高大，似有三层，正是普麽部的祭祀大屋。此处下层也不养牲畜，
打扫得干干净净。宽大的竹梯直通上层。
LONG );
	set("exits",([ /* sizeof() == 1 */
	    "south"  : "/d/dali/luwang",
	    "up"     : "/d/dali/zhulou4",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

