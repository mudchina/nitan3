//Room: huarui3.c

inherit ROOM;

void create ()
{
        set ("short", "华瑞街");
        set("long", @LONG
华瑞街是长安城南一条东西向的大道，也是长安城的居民区。一条碎石子铺
成的街坊，南边可见一些民居住宅，北面是一家花店，街头有炊烟袅袅飘来青柴
的香味。不远处传来家家户户舂米的声音，还有大户人家榨香油的醇香味。
LONG );
        set("exits", 
        ([ //sizeof() == 4
		"south" : "/d/changan/minju3",
        	"north" : "/d/changan/huadian",
        	"west" : "/d/changan/huarui2",
        	"east" : "/d/changan/nanan-daokou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -410);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
