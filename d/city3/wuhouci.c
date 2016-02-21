// Room: wuhouci.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
	set("short", "诸葛亮殿");
        set("long", @LONG
这里是武侯祠的正殿诸葛亮殿。武侯羽扇纶巾一如生前。两边诸葛瞻和诸葛
尚父子塑像也栩栩如生。挂在殿门两壁的，由诗圣杜甫笔下流露的千古名联：『
三顾频繁天下事，两朝开济老臣心。』道尽了这个千古风范的一生心事。
LONG );
	set("exits", ([
	    "southdown" : "/d/city3/liubeidian",
	]));
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -190);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
