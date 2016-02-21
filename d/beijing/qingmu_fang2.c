#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
这里是一间看似很普通的民居，不过却要比通常的民居大了数倍。房间正中
一张长桌，天地会的青木堂的群豪围桌而坐，大声喧谈。
LONG );
       set("exits", ([
                "north" : "/d/beijing/qingmu_dayuan",
        ]));
        set("objects", ([
                 "/d/beijing/npc/guananji" : 1,
                 "/d/beijing/npc/qianlaoben" : 1,
                 "/d/beijing/npc/jialaoliu" : 1,
        ]));
        set("outdoors", "beijing");
        set("coor/x", -60);
	set("coor/y", 200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

