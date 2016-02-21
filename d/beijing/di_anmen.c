#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "地安门");
        set("long", @LONG
这里是是紫禁城地安门，高大的城门正上方刻着『地安门』三个大字，厚实
坚固的古城墙高高耸立着。城门两旁整齐的站着几个卫兵，仔细的监守着这里。
南方由地安门大街通往京城的中心。
LONG );
	set("exits", ([
		"south" : "/d/beijing/di_dajie2",
	]));
	set("objects", ([
		"/d/beijing/npc/ducha" : 1,
		"/d/beijing/npc/bing2" : 1,
		"/d/beijing/npc/bing3" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x", -30);
	set("coor/y", 340);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
