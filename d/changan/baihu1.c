//Room: baihu1.c

inherit ROOM;

void create ()
{
        set ("short", "白虎街");
        set("long", @LONG
白虎街是长安城中心大街，青石板路笔直的伸展出去，一路上行人比肩，笙
歌处处。景物之美，直如神仙境地。西边是扶风道。北面则是阴森森的大牢，有
几个狱卒百无聊赖的呆在门口。
LONG );
        set("exits", 
        ([ //sizeof() == 2
        	"west" : "/d/changan/fufeng1",
        	"east" : "/d/changan/baihu2",
        ]));

	set("objects", ([
		"/clone/npc/xunbu" : 2,
	]));
        set("outdoors", "changan");
	set("no_fight", 1);
        set("coor/x", -410);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

