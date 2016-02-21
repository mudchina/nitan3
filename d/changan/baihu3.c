//Room: baihu3.c

inherit ROOM;

void create ()
{
        set ("short", "白虎街");
        set("long", @LONG
青龙街是长安城中心大街，青石板路笔直的伸展出去，一路上行人比肩，笙
歌处处。景物之美，直如神仙境地。北面东边传出朗朗的读书声，那里是当朝的
学府国子监。
LONG );
        set("exits", 
        ([ //sizeof() == 3
		"north" : "/d/changan/guozijian",
        	"west" : "/d/changan/baihu2",
        	"east" : "/d/changan/fengxu1",
        ]));

        set("outdoors", "changan");
        set("coor/x", -390);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
