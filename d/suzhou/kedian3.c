// Room: /d/suzhou/kedian3.c
// Date: May,31 1998 Java

inherit ROOM;

void create()
{
	set("short", "客店二楼");
        set("long", @LONG
这是一间很大的客房，陈设十分简陋。靠墙放了十几张小木床，不少客人正
和衣而卧，满屋子都是呼呼的打酣声。西边有张床是空的，你蹑手蹑脚地走了过
去。
LONG );
	set("sleep_room", 1);
	set("no_fight", 1);
        set("hotel",1);
	set("no_clean_up", 0);
	set("exits", ([
		"out" : "/d/suzhou/kedian2",
	]));
	set("coor/x", 210);
	set("coor/y", -190);
	set("coor/z", 10);
	setup();
}

int valid_leave(object me, string dir)
{
	if ( dir == "out" ) me->delete_temp("rent_paid");
	return ::valid_leave(me, dir);
}

