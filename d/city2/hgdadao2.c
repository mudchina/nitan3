inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "皇宫大道");
        set("long",
"这里是皇宫内的大道，分外的宽敞平整，不时有一些宫女和太监经过\n"
"，你不敢多看，还是快点朝前走吧，省得招来侍卫的盘查。\n"
);
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north"    : __DIR__"hgdadao3",
                "south"    : __DIR__"hgdadao1",
        ]));

        set("objects", ([

        ]));
        setup();
        replace_program(ROOM);
} 

