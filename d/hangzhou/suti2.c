// suti2.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "苏堤");
        set("long", @LONG
苏堤上，游客们有的林荫大道上漫步吟诗，高谈阔论；有的随机就石，临水
而坐；有的伶立湖边，静享湖景。北边是跨虹桥，南面是东浦桥，西面是去曲园
风荷。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/suti1",
            "south"     : "/d/hangzhou/suti3",
            "west"      : "/d/hangzhou/quyuanbei",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
