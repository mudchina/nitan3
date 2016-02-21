//Room: xian-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "西安大道");
        set("long", @LONG
长安城的主街西安大道颇为热闹，除了本城的居民外，还有不少外来的旅客
和商人。西安大道再向西就是长安城的永泰道口、西城门，往东是故皇宫的扶风
道。
LONG );
        set("exits", 
        ([ //sizeof() == 2
		"east" : "/d/changan/fufeng3",
        	"west" : "/d/changan/xian-daokou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -430);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
