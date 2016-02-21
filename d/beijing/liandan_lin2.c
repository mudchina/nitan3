#include <ansi.h> 
inherit ROOM;
int do_cai(string arg);

void create()
{
        set("short", "城西后林");
        set("long", @LONG
这是一片茂密的树林。很多棵几十丈高的大树聚在一块，象一把把琼天大伞，
连日月都被遮蔽得黯然无光。树林中还不时可以听到大自然发出的声响。
LONG );
        set("exits", ([
                "north" : "/d/beijing/ximenwai",
                "south" : "/d/beijing/liandan_lin6",
                "east" : "/d/beijing/liandan_lin7",
        ]));

        set("outdoors", "beijing");
        set("no_clean_up", 0); 
	set("coor/x", -90);
	set("coor/y", 270);
	set("coor/z", 0);
	setup();       
}

#include "liandan_lin.h"