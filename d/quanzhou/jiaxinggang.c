// Room: /d/quanzhou/jiaxinggang.c
// Date: May 7, 96   Jay

inherit ROOM;

void create()
{
	set("short", "���˺���");
	set("long", @LONG
�����Ǽ��˺��ۣ����ڰ׷���㣬��ͷ��ͣ�źö��洬������
һ�����һ���ȴ����ҡͷ��
LONG );
	set("exits", ([
                "west" : __DIR__"nanhu",
	]));
	set("objects", ([
		"/d/taohua/npc/chuanfu": 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "quanzhou");
	set("coor/x", 100);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
