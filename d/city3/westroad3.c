// Room: westroad3.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "西大街");
        set("long", @LONG
你不知不觉地就来到了成都西北角，从这里往北望，显得格外冷清。青石大
道上只有零零落落的几个人，在慢悠悠闲逛。往南是西大街，东北方向是另一条
大街，西北角有个好大的药店，卖一些武林中人常用的药，唐门弟子常来此配药。
LONG );
        set("outdoors", "chengdu");
	set("exits", ([
	    "south"      : "/d/city3/westroad2",
	    "northeast"  : "/d/city3/northroad1",
	    "northwest"  : "/d/city3/yaodian",
	]));
	set("objects", ([
	    "/d/huashan/npc/haoke": 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -170);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
