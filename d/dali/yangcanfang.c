//Room: /d/dali/yangcanfang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","养蚕房");
        set("long", @LONG
这是一间摆夷族的杆栏民居，此间下层却没有牛羊，三面用竹席围住，似一
个棚屋，中置数座竹架竹盘，饲养着一些桑蚕。一位摆夷姑娘正在用新鲜的桑叶
喂养桑蚕。
LONG );
	set("objects", ([
	   "/d/dali/npc/yangcannu": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "west"  : "/d/dali/buxiongbu",
	]));
	setup();
	replace_program(ROOM);
}

