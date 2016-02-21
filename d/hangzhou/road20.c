// road20.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西湖。大道伸
向东西两边，往北是苏堤。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/suti7",
            "west"      : "/d/hangzhou/road19",
            "east"      : "/d/hangzhou/road16",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
