//Room: tea-shop.c

inherit ROOM;

void create()
{
        set("short", "茶馆");
        set("long", @LONG
这间茶房是长安的闲人杂聚的场所，里面横七竖八的摆放着一些木制的桌椅。
一个说书的老人正在滔滔不绝的讲着什么。一些茶客一边品茶，一边听书，一边
绘声绘色交头接耳，如果你要想打听江湖掌故和谣言，来这里准没错。
LONG );
        set("exits", ([ /* sizeof() == 1 */
        	"south" : "/d/changan/qixiang2",
        ]));
        set("objects", ([
        	"/d/changan/npc/teawaiter" : 1,
        	"/d/changan/npc/laoren" :1,
        ]) );

        set("coor/x", -420);
	set("coor/y", 50);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
