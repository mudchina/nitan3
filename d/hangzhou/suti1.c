// suti1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "苏堤");
        set("long", @LONG
苏堤是诗人苏东坡在主持浚深西湖时用湖泥和草筑成的。苏东坡曾有诗记述
此事；『我在钱塘拓湖渌，大堤士女争昌丰。六桥横绝天汉上，北山始与南屏通。
忽惊二十五万丈，老葑席卷苍烟空。』往北便是大道，南边是跨虹桥。跨虹桥乃
苏堤六桥由北至南的第一座。桥一边是岳湖，桥的另一边是西湖。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/road6",
            "south"     : "/d/hangzhou/suti2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
