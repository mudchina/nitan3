//ROM dating
inherit ROOM;
void create()
{
        set("short", "青龙堂");
        set("long", @LONG
这是『日月神教』下第三大堂：青龙堂的大厅，十分气派，又或有一条青龙
时隐时现。堂梁上有一块匾(bian)。
LONG );
        set("exits", ([
            "south"      : "/d/heimuya/chlang1",
            "northdown" : "/d/heimuya/guang",
        ]));
        set("item_desc", ([
            "bian": "上面写到：长虹贯日，青龙飞天。千秋万载，一统江湖 。\n",
        ]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
