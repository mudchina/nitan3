//Room: /d/dali/qiandian.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","前殿");
        set("long", @LONG
这里是大理国皇宫的前殿，红砖绿瓦建得十分精巧，大理历代国主勤政爱民，
万几宸函，都在此殿。因此大理虽偏处西南的小国，百姓对当朝君臣的爱戴均出
自肺腑，十分真诚。往北就到了御花园, 往南是皇宫大门。
LONG );
	set("objects",([
	   "/d/dali/npc/taijian": 1,
	]));
	set("objects", ([
	    CLASS_D("duan")+"/duanzm": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/yuhuayuan",
	    "south"  : "/d/dali/gongmen",
	]));
	setup();
}
