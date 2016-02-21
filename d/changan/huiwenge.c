//Room: huiwenge.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "汇文阁");
       set ("long", 
"这是一家书局。大堂里摆了一排排的书柜，书架上整整齐齐地放着一些卷轴，\n"
"堂内还悬挂着几盆花花草草，红绿相间，疏密有致，令人赏心悦目。进来就可以\n"
"看到一额横匾:\n"
HIB"         书山有径勤为路\n"
"         学海无涯苦做舟\n"NOR );

        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
        	"/d/changan/npc/shuchi" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -430);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
