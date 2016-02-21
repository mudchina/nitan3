// senlin3.c
inherit ROOM;

void create()
{
        set("short", "百木园");
        set("long", @LONG
这里是梅庄的百木园，你一走到这里，就象走到了一个连绵无尽的小森林一
样，这里无数的松树，柏树，白杨，还有很多叫不出来名字的异种苗木，你走在
其中，只想把这片树林尽情的欣赏一遍，永不出去才好。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "west" : __DIR__"senlin3",
            "north" : __DIR__"senlin2",
            "south" : __DIR__"senlin4",
            "east" : __DIR__"senlin1",
        ]));
        set("objects", ([ /* sizeof() == 1 */
            __DIR__"npc/jiading.c" : 1,
        ]));
        set("outdoors", "meizhuang");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

