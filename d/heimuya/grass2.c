inherit ROOM;
 
void create()
{
        set("short", "草地");
        set("long", @LONG
你走在一片草地。草地西边似乎香气四溢，东边好象是一个小花园。
LONG );
        set("exits", ([
            "west"   : "/d/heimuya/chufang1",
            "east"   : "/d/heimuya/hua1",
             "north" :"/d/heimuya/dating1",
             "south" :"/d/heimuya/grass1",
        ]));
        set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}
