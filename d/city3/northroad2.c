// Room: northroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "北大街");
        set("long", @LONG
这里一条北大街横贯东西。望向北边，是出城的北门。号称 "天下幽" 的青
城山，就是从这里出去。这里地当当道，行人却都过往匆匆，小心翼翼，恨不得
销声匿迹。因为南边一幢古色古香的建筑，就是让天下武林闻风色变的川中唐门。
LONG );
        set("outdoors", "chengdu");
	set("exits", ([
	    "east"   : "/d/city3/northroad3",
	    "west"   : "/d/city3/northroad1",
	    "south"  : "/d/city3/tanggate",
	    "north"  : "/d/city3/northgate",
	]));
	set("no_clean_up", 0);
	set("coor/x", -430);
	set("coor/y", -160);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
	me = this_player();
	if (dir == "south")
	return notify_fail("你一抬足，发现地上有毒，忙抽腿退回。\n");
	else  return 1;
}
