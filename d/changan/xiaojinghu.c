//Room: xiaojinghu.c

inherit ROOM;

void create ()
{
        set ("short", "小镜湖");
        set("long", @LONG
这里就是长安城的小镜湖了。小镜湖的面积并不是很大，但亭台楼阁，假山
长廊却也是有的。建筑的朴素简单，而不奢华。湖水叮叮咚咚的流，世人的烦恼
在这里似乎都消失了。夕阳西下时悠闲的人们总是到这来散步，聊天小憩。
LONG );
        set("exits",([//sizeof() == 1
        	"south" : "/d/changan/huarui4",
        ]));
        
        set("resource", ([ /* sizeof() == 1 */
        	"water" : 1,
        ]));
        
        set("outdoors", "changan");
        set("coor/x", -390);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        
