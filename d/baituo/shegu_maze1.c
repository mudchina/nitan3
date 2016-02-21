// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "蛇谷荒地");
        set("long", @LONG
这里是蛇谷深处，草木大多枯黄凋敝，极是荒僻。四下幽暗寂静，山谷中微
风时起，带来阵阵草木腐败的气味。地上偶尔出现一些小动物的骸骨，不知是被
什麽毒蛇猛兽吃掉了。
LONG );

	set("exits", ([ 
	    "northeast" : __DIR__"shegu18",
	    "southwest" : __DIR__"shegu_maze5",
	    "west" : __DIR__"shegu_maze6",
	]));

	if(random(5) == 0)
	set("objects", ([
	    __DIR__"npc/bt_snake" : 1,
	]));

	set("hide_python", random(2));

	set("cost", 2);
	set("outdoors","baituo");
	set("shegu", 1);
	setup();
}

#include "python_room.h"
