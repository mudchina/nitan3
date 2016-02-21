// Room: /d/xiangyang/jiekou1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "大街口");
        set("long", @LONG
因为这儿是十字街口，所以非常热闹。小商小贩们在向行人吆喝着，兜售他
们的商品。虽然襄阳饱受蒙古军侵扰，但这儿看不出人们有丝毫的紧张，好象他
们已司空见惯、习以为常了。北面和西面是胡同，许多襄阳城的老百姓住在里面，
东面和南面是青石铺就的大街。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"east"  : "/d/xiangyang/northroad1",
		"south" : "/d/xiangyang/westroad2",
		"west"  : "/d/xiangyang/hutong1",
		"north" : "/d/xiangyang/hutong2",
	]));
	set("objects", ([
		"/d/village/npc/seller" : 1,
	]));
	set("coor/x", -320);
	set("coor/y", -50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

