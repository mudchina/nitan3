// Room: /d/suzhou/shuchang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "书场");
        set("long", @LONG
你走进书场，看见里面热热闹闹的，场子里都是听书的，场子前面有一位说
书先生，他看上去四五十岁，手中拿着一块响板，正在聚精会神地说着评书--《
杨家将》。你也逐渐被评书的内容所吸引，场中的人们不时的发出惊叹和喝彩声，
时不时将铜板抛了上去。
LONG );
	set("outdoors", "suzhou");
//	set("no_clean_up", 0);
	set("exits", ([
		"south"  : "/d/suzhou/xidajie2",
	]));
	set("objects", ([
		"/d/suzhou/npc/gongzi": 1,
	]));
	set("coor/x", 180);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
