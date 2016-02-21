//Room: fengxu2.c

inherit ROOM;

void create ()
{
        set ("short", "冯诩道");
        set("long", @LONG
冯诩道是长安城中心大街，青石板路笔直的伸展出去，一路上行人比肩，笙
歌处处。景物之美，直如神仙境地。
LONG );
        set("exits", 
        ([ //sizeof() == 2
		"north" : "/d/changan/fengxu1",
        	"south" : "/d/changan/fengxu3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -380);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
