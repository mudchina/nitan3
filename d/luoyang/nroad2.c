inherit ROOM;

void create()
{
	set("short", "淳熙路");
	set("long", @LONG
淳熙大路是洛阳最整洁的一条大路，街道宽敞而干净，汉白玉砌的路
面被雨水冲得光明如镜，大路两侧的瓦房高大而宏伟，分明便是巨富宅院。
双人合抱的杨树十步一株，整齐的排在两边。东边是衙门所在，西边是则
一家粮铺。
LONG);
        set("outdoors", "luoyang");
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"yamendoor",
  		"north" : __DIR__"nroad3",
  		"south" : __DIR__"nroad1",
  		"west" : __DIR__"liangpu",
	]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
        ]));
	set("coor/x", -170);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
