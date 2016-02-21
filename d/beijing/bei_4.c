#include <room.h>
inherit ROOM;

void create()
{
	set("short", "西单北大街");
        set("long", @LONG
这里是北京城的西单北大街，宽阔的大道向南北走向延伸。街道上的行人接
踵而至，市井的喧哗声、官兵的马蹄声以及小商小贩的吆喝声不断，鱼龙混杂其
中，很是热闹。北方通往地西大街。
LONG );
       set("exits", ([
		"west" : "/d/beijing/bei_3",
		"north" : "/d/beijing/di_1",
		"south" : "/d/beijing/bei_2",
	]));
	set("objects", ([
		"/d/beijing/npc/youren" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x", -50);
	set("coor/y", 290);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
