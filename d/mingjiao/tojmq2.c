//TORJQ2.C

inherit ROOM;

void create()
{
	set("short", "青石大道");
        set("long", @LONG
这里大道平坦，地势开阔，两旁树林中鸟语花香，一片和平安祥的气氛。此
时又有谁能想到，这条大道上撒下过多少江湖中人的血，这片林中又埋有多少惨
死于武林争斗的冤魂的骨。远处，隐约传来叮叮咚咚的伐木声，偶尔能让人追忆
起刀戈铁马的沙场景象。
LONG );
	set("exits", ([
		"northwest" : __DIR__"tojmq3",
		"southeast" : __DIR__"tojmq1",
	]));
	set("no_clean_up", 0);
	set("outdoors", "mingjiao");
	setup();
	replace_program(ROOM);
}
