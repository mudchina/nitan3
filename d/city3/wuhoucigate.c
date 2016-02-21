// Room: wuhoucigate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "武侯祠大门");
        set("long", @LONG
这里原来是武侯祠。大门人进人出，大多缠着武侯巾。原来武侯生前治蜀，
造福两川，这武侯巾乃是他去世川人为其带孝之俗。由于武侯遗爱甚深，虽千载
以下，川人头巾仍不去首。
LONG );
        set("outdoors", "chengdu");
	set("exits", ([
		"northeast" : "/d/city3/southroad3",
		"north"     : "/d/city3/liubeidian",
	]));
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -210);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
