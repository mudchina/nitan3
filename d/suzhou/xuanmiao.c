// Room: /d/suzhou/xuanmiao.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "玄妙观");
        set("long", @LONG
你一走进玄妙观，看到观中香火缭绕，香客众多。殿是重檐歇山式，屋脊高
十几米，内有高大殿柱四十根。屋面坡度平缓，出檐较深，斗拱疏朗宏大，殿内
正中有砖砌须弥座，座上供奉着的三尊高十几米的泥塑三清金身像，法像庄严，
神采奕奕，不失为道教雕塑中的精品。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"north"  : "/d/suzhou/xidajie2",
	]));
	set("coor/x", 180);
        set("coor/y", -225);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
