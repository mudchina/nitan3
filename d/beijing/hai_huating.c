inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","花厅");
        set("long", @LONG
这个花厅是喝酒赏月的佳所，一个小亭子建造在厅的中央，四周围绕着一些
葡萄藤。一阵微风吹过，空气中似乎有隐隐的花香飘来，中人欲醉。
LONG );
	set("exits", ([
		"west" : "/d/beijing/hai_dayuan",
	]));

	set("coor/x", 30);
	set("coor/y", 300);
	set("coor/z", 0);
	setup();
}