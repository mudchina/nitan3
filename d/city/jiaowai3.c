// Room: /d/city/jiaowai3.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "����");
        set("long", @LONG
���ݽ�������֣���֦ͦ�Σ���ľ��б���ּ�С����������Զ�����в�����
�֣�������ת��ʹ���ʱ���⾡����
    �������˺ܶ���֦ʯ�顣
LONG );
    set("exits", ([
        "north" : "/d/city/jiaowai2",
        "south" : "/d/city/jiaowai4",
    ]));
    set("objects", ([
        "/d/city/obj/shitou": 2,
    ]));
//    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", 40);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}
