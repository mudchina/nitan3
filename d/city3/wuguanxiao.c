// Room: wuguanxiao.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "金牛武馆三部");
        set("long", @LONG
这里是「金牛武馆」教授三部，师傅萧飞教授如下技能：基本轻功，基本内
功，基本招架，基本指法，基本暗器。
LONG );
	set("objects", ([
		"/d/city3/npc/xiaofei" : 1,
	]));
        set("no_fight",0);
        set("no_steal",1);
        set("no_beg",1);
	set("no_clean_up", 0);
	set("exits", ([
		"east" : "/d/city3/wuguan",
	]));
	set("coor/x", -420);
	set("coor/y", -150);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
