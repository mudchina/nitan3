//Room: /d/dali/yanchi1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","沿池堤岸");
        set("long", @LONG
这里沿湖堤岸遍植白色的素馨花，故又称『银棱河』；而它的一条分支，堤
岸栽种黄色的迎春花，故称『金棱河』，或金汁河。两河同为滇池的出水口，又
称海口。
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"    : "/d/dali/dianchi",
	    "west"     : "/d/dali/jinzhihe",
	    "eastup"   : "/d/dali/yanchi2",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

