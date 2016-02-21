//Room: /d/dali/yulin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","榕树雨林");
        set("long", @LONG
这是一片湿润的雨林，脚下水汪汪的无路可行，十数丈高的巨大榕树盘根错
节，树干粗得几个人合抱也围不住。榕树的树枝下垂到泥水中反过来扎根，成为
特意的景致。雨林虽然少有走兽，却是飞禽聚居的乐土，身手零活的台夷猎人攀
越在大榕树浮露的根枝上，用短弩射猎飞鸟。
LONG );
	set("objects", ([
	   "/d/dali/npc/lieshou": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"      : "/d/dali/luwang",
	]));
	setup();
	replace_program(ROOM);
}

