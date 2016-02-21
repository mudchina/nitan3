#include <ansi.h>

inherit ROOM;

#define PLACE "hz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "小刀会");
        set("long", @LONG
这里就是小刀会设在杭州的分舵，这里看起来混乱无比，一只破木箱上摆着
几样粗制的赌具，地上乱扔着些鸡骨头，空气中有一股鸡香、酒香和汗臭混杂在
一起的味道。一看就知道是地痞流氓的聚集地。侧面的墙上挂着任务牌（paizi）。
LONG );

        set("objects", ([
               "/d/hangzhou/npc/boss-ma"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : "/d/hangzhou/guozhuang",
        ]));

        setup();
}
#include <bang_bad.h>

