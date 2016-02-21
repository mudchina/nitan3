#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "海港");
        set("long", @LONG
这里是出海的必经之地，福州遥望台湾，中间有个屠龙岛，是一个神秘的地
方，少有人去过，海岸边有一只船(chuan)。
LONG );
        set("exits", ([
                "westup" : "/d/fuzhou/yongquan",
        ]));
        set("item_desc", ([
                "chuan" : "一条大海船。出远海没这样的船可不行。\n",
        ]));
        set("objects", ([
                "/d/fuzhou/npc/boy": 2,
                "/d/fuzhou/npc/girl": 1,
        ]));
//      set("no_clean_up", 0);
        set("outdoors", "quanzhou");
        set("coor/x", 210);
	set("coor/y", -100);
	set("coor/z", 0);
	setup();
//      replace_program(ROOM);
}

void init()
{
    add_action("do_enter", "enter");
}
int do_enter ( string arg )
{
    object ob ;
    //string dir;
    if( !arg || arg !="chuan" ) 
       {
         tell_object(this_player() , "你要 enter 哪儿？\n" ) ;
         return 1 ;
       }
    ob = this_player () ;
    message_vision("船夫一见有人上船，忙叫了一声：开船喽！\n", ob);
    message_vision("船夫升起帆，船就向东方航行。\n", ob);
    ob ->move("/d/fuzhou/dahai") ;
    tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
    call_out("tpenghu", 10 , ob );
    return 1 ;
}
void tpenghu(object ob )
{
    tell_object(ob , "小船航行了很久依旧没有发现任何陆地，你没办法只好返回坐船的地方。\n" ) ; 
    ob->move("/d/fuzhou/haigang");

}

