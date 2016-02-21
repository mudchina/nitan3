// gushan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "孤山");
        set("long", @LONG
通过林荫道向前，迎面石壁上刻有『孤山』两个丹红大字。朝南拾级登山便
是平台。东北边便是发鹤亭。东南边则是平湖秋月。西北边通往西泠桥。
LONG );
        set("exits", ([
            "westup"    : "/d/meizhuang/shijie",
            "east"      : "/d/hangzhou/pinghuqiuyue",
            "southup"   : "/d/hangzhou/gushanpingtai",
            "northwest" : "/d/hangzhou/xilingqiao",
            "northeast" : "/d/hangzhou/fangheting",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
