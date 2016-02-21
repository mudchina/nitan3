inherit ROOM;

void create()
{
        set("short", "尚书府大门");
        set("long",
"这里是京城尚书府大门，经常有人进出，可见尚书大人为国事操劳何\n"
"等之辛苦了，门口有两个家将，看你进来，居然也没来盘问你，真是奇怪。\n"
);
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "west" : __DIR__"ydmen",
                "east" : __DIR__"ssfu",
        ]));

        set("objects", ([
  
        ]));

        setup();
        replace_program(ROOM);
}


