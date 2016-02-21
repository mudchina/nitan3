inherit ROOM;

void create()
{
        set("short", "尚书府");
        set("long",
"这里是京城尚书府了，兵部尚书赵大人经常在这里会客，和接见往来\n"
"传递军情的前线使者。\n"
);
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "west" : __DIR__"ssfmen",
        ]));

        set("objects", ([
               __DIR__"npc/zhao":  1,
        ]));

        setup();
        replace_program(ROOM);
 }
