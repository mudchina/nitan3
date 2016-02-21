#include <room.h>
inherit ROOM;

void create()
{
	set("short", "高升茶馆");
        set("long", @LONG
一座规模不小的茶馆，门前的幡上舞着『高升』两个大字。你刚进来，就闻
到一股茶香沁入心脾，精神为之一爽。几张八仙桌一字排开，坐满了客人，或高
声谈笑，或交头接耳。茶博士摇头晃脑的说着书，茶铺的伙计忙个不停。你要想
打听江湖掌故和谣言，这里是个好所在。
LONG );
       set("exits", ([
		"north" : "/d/beijing/caroad_w2",
	]));
	set("objects", ([
		"/d/beijing/npc/chaboshi" : 1,
		"/d/beijing/npc/teahuoji" : 1,
		"/d/beijing/npc/chake" : 2,
		"/d/beijing/npc/old2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
	replace_program(ROOM);
}

