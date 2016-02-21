// road1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "青石大道");
        set("long", @LONG
大道上挤满了来灵隐寺上香和上飞来峰的游客。北边过了小溪就是灵隐寺了。
南边是上飞来峰的路。
LONG );
        set("exits", ([
                "northwest" : "/d/quanzhou/jxnanmen",
                "northeast" : "/d/hangzhou/road2",
                "north"     : "/d/hangzhou/lingyinsi",
                "south"     : "/d/hangzhou/feilaifeng",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
