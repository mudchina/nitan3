//zsh_szzb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "sz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"紫衫阁"NOR);
        set("long", @LONG
这是一间看上去有些古怪的房间，桌椅门窗尽呈紫色，给人一种神秘莫测的
感觉。厅中端坐一位壮年男子，看上去像一个饱读诗书的文士。房间的墙壁上有
一块牌子(paizi)。紫衫会成员可以在这里选择任务去完成。
LONG );

        set("objects", ([ 
                __DIR__"npc/boss-song"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "south" : __DIR__"zsh_szdamen",
        ]));

        set("coor/x", 180);
	set("coor/y", -220);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>

