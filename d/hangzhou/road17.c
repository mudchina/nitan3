// road17.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上游人，或步行，或乘轿，或骑马。个个喜气洋洋的来游西湖。大道伸
向南北两边，往西是虎跑泉，往东是一条山路。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/road18",
            "south"     : "/d/hangzhou/qiantang",
            "west"      : "/d/hangzhou/hupaoquan",
            "east"      : "/d/hangzhou/kslu",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/tiao-fu" : 1,
            "/d/hangzhou/npc/chuyuan" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
