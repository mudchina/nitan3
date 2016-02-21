#include <room.h>
inherit ROOM;

void create()
{
	set("short", "地东大街");
        set("long", @LONG
这里是北京城地安门的东街。街道是整整齐齐的杨树林，道上行人络绎不绝，
车辆马匹穿插其中。大街上有闲逛的游人，上京赶考的考生，背负着担子的挑夫
以及正在玩耍着的幼童构出了一幅繁忙热闹的盛世景象。北边是文庙。南边是宽
阔的王府井大街。
LONG );
       set("exits", ([
		"north" : "/d/beijing/wenmiao",
		"south" : "/d/beijing/wang_9",
		"west" : "/d/beijing/dong_2",
	]));
	set("objects", ([
		"/d/beijing/npc/shusheng1" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x", -10);
	set("coor/y", 320);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
