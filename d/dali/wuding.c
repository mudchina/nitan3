//Room: /d/dali/wuding.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","武定镇");
        set("long", @LONG
这里是台夷分支卢鹿族罗蝥部的治府，罗蝥部除了这武定州外还辖元谋、禄
定两镇。此镇不大，正处山中竹林深处，显得格外清幽。卢鹿族人的竹楼四散分
布在竹林中。
LONG );
	set("objects", ([
	   "/d/dali/npc/guniang": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"      : "/d/dali/zhulou1",
	    "northeast"  : "/d/dali/zhulin",
	    "west"       : "/d/dali/qingzhulin",
	    "south"      : "/d/dali/nongtian1",
	]));
	setup();
	replace_program(ROOM);
}

