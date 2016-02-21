//Room: /d/dali/feilihueast.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","妃丽湖东");
        set("long", @LONG
你站在妃丽湖的东岸，脚下的土路绕湖东连接南北的村镇。眺望湖中只见轻
舟点点，正是捕鱼的台夷竹筏。路边尽是青青竹林，台夷的竹楼间或出现。向西
南去的岔路通往湖西的休猎部，正路向南直达龙口城。
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "south"      : "/d/dali/longkou",
	    "northwest"  : "/d/dali/feilihu",
	    "southwest"  : "/d/dali/hexi",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

