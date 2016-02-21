//Room: /d/dali/tusimentang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","门堂");
        set("long", @LONG
门堂以及其他一些附属建筑，如谷仓，厨房，坚狱，外有二米多高重修的围
墙。主体建筑是规模最大的议事厅，三层大屋系三重蟾歇山顶干栏式建筑，长六
十尺，宽四十有五，高三十尺。二楼是宣抚召集大小头领议会地点，也是审判室。
LONG );
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/tusihouting",
	    "up"     : "/d/dali/tusiyishi",
	    "out"    : "/d/dali/tusifu",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

