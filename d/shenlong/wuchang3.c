// wuchang3.c

inherit ROOM;

void create()
{
	set("short", "练武场");
        set("long", @LONG
这是一个比西面更为宽大的练武场，许多手执短剑的少年少女在这里练功。
有的也在一旁观看，似乎在揣摩什么。
LONG );
	set("exits", ([
		"west" : __DIR__"wuchang",
	]));
	set("objects", ([
                "/clone/npc/mu-ren": 4,
	]));
        setup();
	replace_program(ROOM);
}
