//Room: baihu2.c

inherit ROOM;

void create ()
{
        set ("short", "白虎街");
        set("long", @LONG
白虎街是长安城中心大街，青石板路笔直的伸展出去，一路上行人比肩，笙
歌处处。景物之美，直如神仙境地。往南就是故皇宫的金水桥了，北面有一条大
路通向长安城北门。
LONG );
        set("exits", 
        ([ //sizeof() == 4
        	"south" : "/d/changan/bridge1",
		"north" : "/d/changan/beian-dadao",
        	"west" : "/d/changan/baihu1",
        	"east" : "/d/changan/baihu3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -400);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
