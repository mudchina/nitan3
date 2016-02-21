#include <room.h>
inherit ROOM;

void create()
{
        set("short", "杨柳胡同");
        set("long", @LONG
这里是杨柳胡同的底端，走到这里，行人已经不多见了。一路上，胡同两旁
四合院的大门紧闭着，唯独这里南边的一个四合院大门是敞开着的。你不禁
想去看一看。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yangliu2",
                "south" : "/d/beijing/qingmu_men",
        ]));

        set("outdoors", "beijing");
        set("coor/x", -60);
	set("coor/y", 230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

