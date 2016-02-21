// Room: /d/suzhou/hanshidian.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "寒拾殿");
        set("long", @LONG
这里供奉着相传为『和合二仙』化身的寒山，拾得金身塑像，形态生动，逗
人喜爱。寒山寺每年除夕半夜，撞钟一百零八响，其含义是除旧迎新和纪念佛门
一百零八位高僧。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
		"out"   : "/d/suzhou/fengqiao",
		"west"  : "/d/suzhou/zhengdian",
	]));
	set("coor/x", 140);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

