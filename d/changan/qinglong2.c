//Room: qinglong2.c

inherit ROOM;

void create ()
{
        set ("short", "青龙街");
        set("long", @LONG
青龙街是长安城中心大街，青石板路笔直的伸展出去，一路上行人比肩，笙
歌处处。景物之美，直如神仙境地。往北就是故皇宫的金水桥了，南面有一条大
路通向长安城南门。
LONG );
        set("exits", 
        ([ //sizeof() == 4
        	"north" : "/d/changan/bridge2",
		"south" : "/d/changan/nanan-dadao",
        	"west" : "/d/changan/qinglong1",
        	"east" : "/d/changan/qinglong3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -400);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
