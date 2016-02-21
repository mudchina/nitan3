// Room: /city/wudao1.c

#include <ansi.h>

inherit "/d/city/underlt";

void create()
{
        set("short", "武道场");
        set("long", @LONG
这里是三面环山，只有北面有条出口的一坪山间平地。山坡山阵阵松涛哗哗
作响，山脚下的平地绿草如茵，中间架起了个擂台，四周一溜过去搭着凉棚，棚
中桌椅杯盆俱全。这里是少年组的比武场地！
LONG );
        set("outdoors", "city");
        set("exits", ([
                "leitai"      : "/d/city/leitai",
                "east"        : "/d/city/wudao4",
                "north"        : __DIR__ "biwu_gate",
//                "south"        : __DIR__ "mishuchu",
        ]));
        set("no_fight", 1);
	set("coor/x", -60);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        init_here();
        replace_program("/d/city/underlt");
}
