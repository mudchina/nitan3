// road3.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道两边遍植青松，满目苍翠，偃盖如雪。被称为『九里雪松』。东北边是
洪春桥。再向西南便到了灵隐寺。南边是一条土路。
LONG );
        set("exits", ([
            "southup"     : "/d/hangzhou/huangniling",
            "southwest"   : "/d/hangzhou/road2",
            "northeast"   : "/d/hangzhou/hongchunqiao",
        ]));
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
