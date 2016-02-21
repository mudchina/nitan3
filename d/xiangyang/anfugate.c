// Room: /d/xiangyang/anfugate.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "安抚使衙门");
        set("long", @LONG
这是安抚使衙门的大门，铜皮包门似乎极为沉重，上面有两个明晃晃的铜环；
大门紧闭，里面却传出一阵阵嬉笑声，和门口的肃杀很不协调。想来这个安抚使
大人的日子还是过得蛮滋润的。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"south" : "/d/xiangyang/anfupailou",
	]));
	set("coor/x", -290);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
