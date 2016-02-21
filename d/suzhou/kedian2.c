// Room: /d/suzhou/kedian2.c
// Date: May,31 1998 Java

inherit ROOM;

void create()
{
	set("short", "客店二楼");
        set("long", @LONG
你正走在客店二楼的走廊上，可以听到从客房里不时地呼呼的打酣声，一阵
高过一阵。不时有睡意朦胧的旅客进进出出，到楼下的掌柜处付了钱再上来睡觉。
LONG );
	set("exits", ([
		"down"  : "/d/suzhou/kedian",
		"enter" : "/d/suzhou/kedian3",
	]));
	set("no_clean_up", 0);
	set("coor/x", 210);
	set("coor/y", -190);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

