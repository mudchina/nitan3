//room: didao6.c
inherit ROOM;

void create()
{
  set("short","秘道尽头");
        set("long", @LONG
你忽觉前方一亮，身前真是别有洞天，前方好想有作花园。不知是什么地方。
LONG );
  set("exits",([
      "north"     : "/d/heimuya/xiaohuayuan",
      "northdown" : "/d/heimuya/didao4",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
