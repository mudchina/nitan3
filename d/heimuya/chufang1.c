//chufang1.c
inherit ROOM;
void create()
{
  set("short","厨房");
        set("long", @LONG
你走在一条阴暗的林间小道上，两旁是阴森森的树林。一阵这是风雷堂的厨
房，一位美丽侍女满脸堆笑。整个房间菜香胭脂香迷漫。墙上贴着一张醒目的启
事(note)。
LONG );
  set("exits",([
      "east" : "/d/heimuya/grass2",
  ]));
  set("item_desc",([
      "note" : "人是铁，饭是钢，一顿不吃饿得慌。\n",
  ]));

  set("objects",([
      "/d/heimuya/npc/shinu" : 1,
    "/d/heimuya/obj/tea" : 1 + random(5),
      "/d/heimuya/obj/sherou"  : random(4),
  ]));
//  set("no_clean_up", 0);
  setup();
}
int valid_leave(object me, string dir)
{
	if (( present("tea", me)||present("she rou", me))
	&&objectp(present("shi nu", environment(me))) )
	return notify_fail
	("侍女美目一挑，你还是在这儿吃完吧。\n");
	return ::valid_leave(me, dir);
}

