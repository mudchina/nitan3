// road14.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
沿湖大道旁店铺林立，长街古朴，屋舍鳞次栉比，道上人来车往，一片太平
热闹景象。西边有一花园，游人进进出出，十分热闹。东边是名医胡庆余开的药
铺。
LONG );
        set("exits", ([
            "northeast" : "/d/hangzhou/road13",
            "southwest" : "/d/hangzhou/road15",
            "east"      : "/d/hangzhou/yaodian",
            "west"      : "/d/hangzhou/qingbomen",
        ]));
        set("objects", ([
            "/d/hangzhou/honghua/wen" :1,
            "/d/hangzhou/honghua/luo" :1,
        ]));
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
