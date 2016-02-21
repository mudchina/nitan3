// Room: /d/suzhou/dongmen.c
// Date: May 31, 98  Java

inherit ROOM;

string look_gaoshi();
void create()
{
	set("short", "东门");
        set("long", @LONG
这是号称天堂的苏州东城门，城门正上方刻着『东门』两个楷书大字，城墙
上贴着几张官府告示(gaoshi)。官兵们警惕地注视着过往行人，你最好小心为妙。
一条笔直的青石板大道向东西两边延伸，西边是城里。
LONG );
	set("outdoors", "suzhou");
//	set("no_clean_up", 0);
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"west" : "/d/suzhou/dongdajie2",
		"east" : "/d/quanzhou/qzroad2",
	]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", 250);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n苏州知府\n冯正东\n";
}

