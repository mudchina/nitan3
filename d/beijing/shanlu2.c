inherit ROOM;

void create()
{
	set("short", "山路");
        set("long", @LONG
这里是荒凉的山路，只有一条蜿蜒崎岖的小径，这里荒无人烟，让人觉得背
后冷飕飕的。
LONG );
	set("exits", ([
		"westup"    : "/d/beijing/shanlu3",
		"southdown" : "/d/beijing/shanlu1",
	]));
 	set("outdoors", "beijing");
	setup();
	replace_program(ROOM);
}
