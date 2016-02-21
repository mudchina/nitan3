//Room: /d/dali/titian1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","梯田");
        set("long", @LONG
东泸水河谷气候较温暖，乌夷先民沿山坡开垦了不少梯田。此间乃是低坡，
层层梯田沿坡而上，土地看来并不肥沃，作物较稀疏，乌夷地区农业颇为落后，
多行换季轮耕，附近山上的一些梯田在这个季节正荒芜着。
LONG );
	set("objects", ([
	   "/d/dali/npc/nongfu": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"      : "/d/dali/zhenxiong",
	]));
	setup();
	replace_program(ROOM);
}

