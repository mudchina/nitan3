// ximenroad2.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "树林");
        set("long",
"唐家镇郊外的树林，松枝挺拔，乔木横斜。林间小道，逶迤随远。林\n"
"中蝉鸣厮闹，鸟啼宛转，使你顿时烦意尽消。再往前就到了蜀中唐门了。\n"
);
        set("exits", ([
                "northup" : __DIR__"gudao1",
                "southdown" : __DIR__"ximenroad",
        ]));
        set("outdoors", "蜀中");
        setup();
        replace_program(ROOM);
}
