inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰错落，林壑幽深，溪泉飞瀑，
云雾缭绕，不觉心胸大快。山路东西通向磨镜台和天柱峰。
LONG);
        set("exits", ([
               "westup"    : __DIR__"tianzhu",
               "eastdown"  : __DIR__"mojingtai",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

        set("coor/x", -70);
	set("coor/y", 40);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}

