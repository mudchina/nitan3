// Room: /d/xiangyang/jiedao.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "街道");
        set("long", @LONG
这里是襄阳城内有钱人的居住区。街道两旁是一些豪华的住宅，虽然襄阳历
经战乱，但还有许多有钱人没搬走，为坚守襄阳城出钱出力。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"east"  : "/d/xiangyang/minju1",
		"west"  : "/d/xiangyang/minju2",
		"north" : "/d/xiangyang/eastjie2",
	]));
	set("objects", ([
		"/d/xiangyang/npc/poorman" : 2,
	]));
	set("coor/x", -270);
	set("coor/y", -100);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

