//Room: fufeng4.c

inherit ROOM;

void create ()
{
        set ("short", "�����");
        set("long", @LONG
������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·�����˱ȼ磬��
�账��������֮����ֱ�����ɾ��ء�
LONG );
        set("exits", 
        ([ //sizeof() == 2
        	"north" : "/d/changan/fufeng3",
        	"south" : "/d/changan/fufeng5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -420);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}