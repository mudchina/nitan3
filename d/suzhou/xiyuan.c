// Room: /d/suzhou/xiyuan.c
// Date: May,31 1998 Java

inherit ROOM;

void create()
{
	set("short","戏园子");
        set("long", @LONG
这是一座苏州城里鼎鼎有名的戏园，戏园中生，旦，净，墨，丑一应具全，
场中一个大戏台，台上正在唱着《遇长春》，台下不时地传来票友们的叫跃，喝
彩声。你也忍不住想坐下来看看戏，放松一下筋骨。
LONG );
//	set("no_clean_up", 0);
	set("objects", ([
		"/d/suzhou/npc/piaoyou": 3,
	]));
	set("exits",([ /* sizeof() == 1 */
		"northeast" : "/d/suzhou/beidajie1",
		"north"     : "/d/suzhou/majiu",
	]));
	set("coor/x", 190);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
