//Room: /d/dali/chahuashan5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","茶花山");
        set("long", @LONG
你走在茶花山上，这里遍地是生长茂盛的茶花。当然，大部分是凡品，但偶
尔也会有一两株佳品藏匿其中。西望不远是大理城的北门，南边不远是城墙。
LONG );
	set("objects", ([
	   "/d/dali/obj/shanchahua": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "eastdown" : "/d/dali/chahuashan6",
	    "west"     : "/d/dali/chahuashan2",
	]));
	setup();
	replace_program(ROOM);
}

