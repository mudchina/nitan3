inherit ROOM;

void create()
{
        set("short", "南街广场");
        set("long",
"这里是南街广场了，由于靠近汴梁城中心，这里更为繁华，西边是一\n"
"个妓院，据说京城第一名妓“李师师”就是自那里出名的，看着往来买笑\n"
"之人蜂拥不绝，当可知道传言非虚也，东边是个绸缎庄，里面经营的各种\n"
"布匹很受达官贵人们的青睐。\n"
);
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north" : __DIR__"center",
                "south" : __DIR__"nandajie1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

