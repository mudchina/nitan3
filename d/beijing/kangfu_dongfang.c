inherit ROOM;

void create()
{
	set("short", "东厢房");
        set("long", @LONG
这里是康亲王府的左边的一个厢房，是供给王府的客人所居住的。厢房中央
摆着几张大床，几张桌子。室中光线柔和，使人更增睡意。
LONG );
	set("exits", ([
		"west" : "/d/beijing/kangfu_zoulang2",
	]));

       set("no_fight",1);
       set("no_steal",1);
       set("sleep_room",1);
	set("no_clean_up", 0);
	set("coor/x", -20);
	set("coor/y", 310);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}