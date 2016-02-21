// Room: fuheqiaoe.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short","府河桥");
        set("long", @LONG
这里是成都东门外府河桥。成都自古就是川中首府，府河和南河夹城而过，
成为天然的护城河。由于四川外有峡江，秦岭之险，内仗绵渝坚城之固，成都却
因之自来无坐守成功之绩。往往兵到城下，降旗高扯了。
LONG );
	set("outdoors", "chengdu");
	set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/city3/road2",
            "west"  : "/d/city3/eastgate",
	]));
	set("no_clean_up", 0);
	set("coor/x", -390);
	set("coor/y", -180);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

