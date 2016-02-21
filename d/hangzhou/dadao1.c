// dadao1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "沿湖大道");
        set("long", @LONG
一条宽敞的大道上却游人稀少。原来这里沿路住着的都是达官贵人。本来风
景秀丽之处，却显的一片萧瑟。路的西边是一座庄园，大道向南北延伸。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/road5",
            "south"     : "/d/hangzhou/dadao2",
            "west"      : "/d/hangzhou/guozhuang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
}
