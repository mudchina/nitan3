//Room: /d/dali/yangzong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","阳宗镇");
        set("long", @LONG
这里是强宗部的村镇，是么些蛮族的聚居区域，么些蛮族是摆夷的一支。此
处也是山间的小型平原，北面临着一片绿水，叫做明湖，这地方略微偏远些，但
有相当不少的摆夷人生活在附近。西南方有道路通向其它村镇。
LONG );
	set("objects", ([
	   "/d/dali/npc/bshangfan": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "westup"     : "/d/dali/shanlu8",
	    "northeast"  : "/d/dali/nongtian4",
	    "southup"    : "/d/dali/sanglin",
	    "southwest"  : "/d/dali/milin",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

