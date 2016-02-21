//road1.c 黄土路
// by Xiang

inherit ROOM;

void create()
{
        set("short", "乱石坡");
        set("long", @LONG
这是一处乱石怪异的小山岗，向东北是通往平定州的小路。据说前方经常有
野兽出没，不可久留。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "northeast" : "/d/heimuya/road2",
            "southwest" : "/d/heimuya/road4",
            "west"  : "/d/heimuya/linjxd1",
            "east"  : "/d/heimuya/dating4",
        ]));
        set("objects",([  
           "/d/heimuya/npc/laozhe" : 1 ,
        ])); 
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
