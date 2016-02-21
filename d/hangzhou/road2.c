// road2.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西边是灵隐寺
和飞来峰。往南是上天竺。
LONG );
        set("exits", ([
                "southup"   : "/d/hangzhou/shanlu1",
                "southwest" : "/d/hangzhou/road1",
                "northeast" : "/d/hangzhou/road3",
        ]));
        set("objects", ([
           "/d/hangzhou/npc/xianghuo" : 1,
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
