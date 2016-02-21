//JMQSHULIN4.C

inherit ROOM;

void create()
{
	set("short", "巨木旗树林");
        set("long", @LONG
你眼前骤然一暗，朦胧中，只见左右前后，到处都是铺天盖地的不知名的巨
树，好象松柏，又似冷杉，簇在一起，密实的枝叶象一蓬蓬巨伞恒伸向天空，遮
天蔽日。你似乎迷失了方向，象没头苍蝇般到处乱闯。
LONG );
	set("exits", ([
                     "east" : __DIR__"jmqshulin3",
		"west" :__DIR__"jmqshulin4",
		"north" : __DIR__"jmqshulin5",
		"south" : __DIR__"jmqshulin4",
	]));
        set("objects", ([
                __DIR__"obj/pine" : random(5),
        ]));
	set("outdoors", "mingjiao");
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
