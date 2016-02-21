#include <room.h>
inherit ROOM;

void create()
{
	set("short", "虎坊路");
        set("long", @LONG
这里是京城的虎坊路，它西接凡陛桥。只要你身上有两钱儿，在这里就会受
到热情的招呼。任何你不知道的事，在这里打听一下，都可以知道个八九不离十。
南边有一家小小的面馆，从里面传来一阵轰闹声。
LONG );
	set("exits", ([
		"south" : "/d/beijing/mianguan",
		"east" : "/d/beijing/fu_2",
	]));

	set("outdoors", "beijing");
	set("coor/x", 10);
	set("coor/y", 320);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
