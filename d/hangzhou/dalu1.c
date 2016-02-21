// dalu1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "大路");
        set("long", @LONG
路的东边是一座小山。山上郁郁葱葱，种满了树。山上本是一处观赏西湖的
好地方，但却被丁财主占为私有。大路向东北和南延伸。
LONG );
        set("exits", ([
            "northeast" : "/d/hangzhou/dadao2",
            "south"     : "/d/hangzhou/dadao3",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/tiao-fu": 1,
            "/d/hangzhou/npc/honghua1" : 2,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
}
