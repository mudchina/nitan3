// Code of ShenZhou
// wsky, 5/7/00
inherit ROOM;

#include <ansi.h>
#include "xx_job.h"

void setup_npc(object me, object ob);

void create()
{
        set("short", "星宿密林");
        set("long", @LONG
这里是星宿海旁边的森林，高大的松树几乎把所有的光线都遮掩住了。地上
到处都是残枝败叶，每踏出一步都会发出吱吱的声响，远处不时传来一阵阵枭鸣，
使人毛骨悚然。
LONG );

        set("exits", ([ 	
             "northeast" : "/d/xingxiu/forest7",
	     "east" : "/d/xingxiu/xxroad10",
        ]));
/*
        set("objects", ([
                "/d/xingxiu/npc/sangtu"  : 1,
        ]) );
*/
        set("no_clean_up", 0);

        set("outdoors", "xingxiuhai");

        set("cost", 2);
        setup();
        

}
