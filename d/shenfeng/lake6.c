
inherit ROOM;

void create()
{
	set("short", "湖边");
        set("long", @LONG
只见湖边红花树下，坐着一个全身黄衣的少女，长发垂肩，正拿
着一把梳子慢慢梳理。她赤了双脚，脸上发上都是水珠。只见她舒雅
自在的坐在湖边，明艳圣洁，仪态不可方物，黄衣倒映水中，落花一
瓣一瓣的掉在她头上、衣上、影子上。任尔平时如何潇洒自如，此时
竟呐呐的说不出话来。
LONG );
	set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"conglin1",
                "east" : __DIR__"lake5",
]));
	set("objects", ([ /* sizeof() == 1 */
                "/d/hangzhou/honghua/huo" :1, 
        ]));
	set("outdoors", "shenfeng");
	set("no_new_clean_up", 0);

	setup();
	replace_program(ROOM);
}
