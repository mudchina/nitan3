#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"马军大营"NOR);
        set("long", @LONG
这里就是「大宋」马军大营，营内军马嘶鸣，尘土飞扬，为了应对蒙古
精锐的骑兵，大宋早已开始了骑兵的训练，较场中央指挥的将领虽然早已汗
流浃背，可是丝毫也不敢懈怠。
LONG
);
        set("train", "cavalry");  
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "west"  :   __DIR__"sying1",
        ]));

        set("objects", ([

        ]));

        setup();
}

