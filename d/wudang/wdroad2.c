inherit ROOM;

void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
������һ����ʯ����ϣ�������Լ�ɼ������ݳǵ��ϳ�ǽ��
�˴���������ȥ�����Կ���һ������
LONG);
        set("outdoors", "wudang");
        set("exits", ([
                "south" : __DIR__"wdroad3",
                "north" : __DIR__"wdroad1",
                "southeast" : "/d/guiyun/yixing",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -280);
	set("coor/y", -140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}