//Room: /d/dali/wuyiminju4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","乌夷民居");
        set("long", @LONG
这是一座用木柴及兽皮搭成的乌夷民居。此地的村民主要从事耕作，由于实
行换季轮耕，不得不经常迁徙，因而房舍都颇简陋，说是房舍，倒不如说更象帐
篷，拆、建都甚方便。
LONG );
	set("objects", ([
	   "/d/dali/npc/kid": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/yixibu",
	]));
	setup();
	replace_program(ROOM);
}

