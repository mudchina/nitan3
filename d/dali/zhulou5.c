//Room: /d/dali/zhulou5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","祭祀屋");
        set("long", @LONG
此间乃竹楼顶层，是一间宽敞的大屋，正中一座祭台上十二白石围成一圈，
当中立有一面竹牌，上绘本族的蛇神图画；圈内另有几面稍小的竹牌，上书族内
祖先姓名尊号；祭台前香火贡品整齐放置，时有族人前来顶礼膜拜。
LONG );
	set("objects", ([
	   "/d/dali/npc/jisi": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "down"  : "/d/dali/zhulou4",
	]));
	setup();
	replace_program(ROOM);
}
