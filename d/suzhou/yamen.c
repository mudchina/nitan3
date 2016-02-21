// Room: /d/suzhou/yamen.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "苏州府衙");
        set("long", @LONG
堂上东西有两根楹柱，挂着一幅对联，但是你根本无心细看。正墙上悬挂一
个横匾，上面横书『正大光明』四个金光闪闪的大字。『肃静』『回避』的牌子
分列两侧。知府正坐在文案后批阅文书，师爷随侍在后。
LONG );
	set("outdoors", "suzhou");
//	set("no_clean_up", 0);
	set("exits", ([
		"south"  : "/d/suzhou/xidajie1",
	]));
	set("objects", ([
		"/d/suzhou/npc/feng": 1,
		"/d/suzhou/npc/shiye": 1,
		"/d/suzhou/npc/yayi": 4,
	]));
	set("coor/x", 190);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
