// Room: /city3/tidufu.c
// Date: Feb.14 1998
inherit ROOM;

void create()
{
        set("short", "提督府");
        set("long", @LONG
这里便是提督大人办公事的地方。正前方 (front)大红楠木案桌后正经端坐
着的，就是成都提督吴天德。两边站立纹丝不动的是他的亲兵侍从，看上去都十
分彪悍。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : "/d/city3/tidugate",
        ]));
        set("objects", ([ /* sizeof() == 1 */
             "/d/city3/npc/wutiande" : 1,
             "/d/city3/npc/shicong"  : 2,
             "/d/city3/npc/qinbing" : 4,
        ]));
        set("item_desc",([
            "front" : "
                ###########################
                #                         #
                #    民   安   境   靖    #
                #                         #
                ###########################
                            !~A~!
                      @~~~~~!(O)!~~~~~@
                           (.@ @.)
                            . ~ .
                         /   ~.你奶奶的...你这刁民...还瞧甚麽? 不认得老爷麽? ...
                        #           #
             HHHH     #               #
             HHHH   #    n         n    #
          |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
           ```````````````````````````````````````
                  ()                      ()
                 ()                        ()
                ()                          ()
               ()                            ()\n"
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -430);
	set("coor/y", -160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
