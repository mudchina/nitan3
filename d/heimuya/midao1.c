// Room /d/heimuya/midao1.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "秘道");
        set("long", @LONG
这是日月神教极其秘密的通道。是黑木崖与中原教众取得联系的捷径。
LONG );
     set("exits", ([
         "out"       : "/d/heimuya/house1",
         "southdown" : "/d/heimuya/midao2",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}

