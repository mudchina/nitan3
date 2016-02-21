// Room: southgate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
	set("short", "南门");
        set("long", @LONG
这是成都南城门，城门正上方刻着『南门』两个楷书大字，城墙上贴着几张
官府告示(gaoshi)。一条笔直的青石板大道向南延伸。南边是郊外，遍地麦浪金
黄迷人。北边是城里。
LONG );
        set("outdoors", "chengdu");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("no_fight",0);
	set("exits", ([
		"south"  : "/d/city3/nanheqiaos",
		"north"  : "/d/city3/southroad2",
	]));
	set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing"    : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -430);
	set("coor/y", -210);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n成都提督\n吴天德\n";
}
