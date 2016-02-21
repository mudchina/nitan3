// ROOM : linjxd5.c
inherit ROOM;
void create()
{
  set("short","林间小道");
        set("long", @LONG
你走在一条阴暗的林间小道上，两旁是阴森森的树林。一阵阵风吹过树梢，
发出沙沙的响声，令你不寒而栗。忽然你发现树丛中有两点绿芒，一闪即没！！
LONG );
  set("exits",([
      "southup" : "/d/heimuya/dating1",
      "north" : "/d/heimuya/linjxd4",     
      "east"  : "/d/heimuya/linjxd3",
      "west"  : "/d/heimuya/linjxd5",
  ]));
  set("objects",([
      "/d/heimuya/npc/wolf" : 4 ,
  ]));
//  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
