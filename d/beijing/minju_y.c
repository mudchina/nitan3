#include <room.h>
inherit ROOM;

void create()
{
	set("short", "四合院");
        set("long", @LONG
四合院是北京民居的典型，杨柳胡同中的这个四合院看来已经过了一段很长
久的历史了。四合院的大门破旧不堪，大门原本漆着的颜色已无法辨认，门上还
贴着一幅残破的对子，字迹模糊不清，猜想也就无非是些『万事如意』什么的。
你刚跨进四合院的大门，院内的居民用奇怪的眼神上下打量着你，没事还是趁早
离开吧。
LONG );
       set("exits", ([
		"east" : "/d/beijing/yangliu1",
	]));
	set("objects", ([
		"/d/beijing/npc/jumin1" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x", -70);
	set("coor/y", 250);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

