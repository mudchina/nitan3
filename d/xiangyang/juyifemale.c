// Room: /d/xiangyang/juyifemale.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "女客房");
        set("long", @LONG
这是间整洁的厢房，因门窗常闭着，光线很昏暗。房里别无他物，只有两边
放着几张收拾得舒舒服服的大床，看着就让人想睡觉。
LONG );
	set("sleep_room", "1");
	set("no_clean_up", 0);

	set("exits", ([
		"west" : "/d/xiangyang/juyihuayuan",
	]));
	set("coor/x", -310);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

