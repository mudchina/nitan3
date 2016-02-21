// Room: /d/xiangyang/tiejiangpu.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "兵器铺");
        set("long", @LONG
这里原来是一家极其简陋的铁匠铺。近年来蒙古大军屡次进犯襄阳，这家铁
匠铺被官府征用，作为官办作坊。目前规模很大，一般用来为襄阳守军打造铠甲、
兵器等，近来因襄阳需筹备守城物资，奉郭夫人之命也生产一些铁钎、铁锤、伐
木斧头等。只见几十个铁匠正叮叮当当地忙个不停。
LONG );
	set("exits", ([
		"west" : "/d/xiangyang/southjie3",
	]));
	set("objects", ([
                "/d/city/npc/smith" : 1,
	]));
	set("coor/x", -280);
	set("coor/y", -120);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

