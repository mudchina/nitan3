//ROM dating
inherit ROOM;
void create()
{
        set("short", "白虎堂");
        set("long", @LONG
这是『日月神教』下第二大堂：白虎堂的大厅，四目望去，一地都是鲜血，
显然不久前这里有一场大战。堂梁上有一块旧木匾(bian)。堂上北壁上有几个血
字(zi)。
LONG );
        set("exits", ([
            "west" : "/d/heimuya/baistep1",
            "east" : "/d/heimuya/linjxd6",
        ]));
        set("item_desc", ([
            "bian": "上面写到：长河落日，白虎在天；
                     千秋万载，一统江湖 。\n",
            "zi" : "上面写到：华山弟子，势杀邪教。\n" 
	]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
