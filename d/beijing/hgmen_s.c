inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","皇宫正门");
        set("long", @LONG
这里便是皇宫的正门，丈高的朱红大门敞开着，门上金色的铆钉闪闪发光。
大门两旁站着两排神情严肃的卫兵，不停的打量着过往的行人。灿烂的阳光直射
在巍峨雄伟的古城墙上，使得城墙上方『紫禁城』三个烁金大字显得格外的耀眼。
从南方的金水桥可以穿越护城河到达繁华的天安门广场。[2;37;0m
LONG );
	set("exits", ([
		"south" : "/d/beijing/qiao",
		"north" : "/d/beijing/hg",
	]));
	set("objects", ([
		"/d/beijing/npc/bing2" : 2,
		"/d/beijing/npc/yuqian1" : 1,
	]));
	set("no_fight", 0);
	set("coor/x", -30);
	set("coor/y", 280);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (objectp(ob = present("guan bing", environment(me))) && dir == "north")
                return notify_fail(ob->name() + "伸手拦住你朗声说道：皇宫重地，岂容寻常百姓出入。\n\n");
        if (objectp(ob = present("shi wei", environment(me))) && dir == "north")
                return notify_fail(ob->name() + "伸手拦住你朗声说道：皇宫重地，岂容寻常百姓出入。\n\n");
        return ::valid_leave(me, dir);
}
