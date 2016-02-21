//Room: /d/dali/dalangan1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","");
        set("long", @LONG
依着一棵大榕树，摆夷人在此建了一座相当大的杆栏。下层这里有一满圈的
十几头牛羊。旁边的楼梯修得颇宽。看来这里是本地的体面人家。
LONG );
	set("objects", ([
	   "/d/dali/npc/shanyang": 3,
	   "/d/dali/npc/cow": 2,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"  : "/d/dali/nongtian4",
	    "up"    : "/d/dali/dalangan2",
	]));
	setup();
	replace_program(ROOM);
}

