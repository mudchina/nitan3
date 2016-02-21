//lhqmen.c

inherit ROOM;

void create()
{
        set("short", "烈火旗大门");
        set("long", @LONG
这里是明教烈火旗的大门，庄严古朴，门前对插四面镶红飞龙旗。金色门钉
扣在火漆红门上，分外精神。也是通往明教总舵的必经之地。所以来往的人也特
别多。
LONG );
        set("exits", ([
                "enter"     : __DIR__"lhqyuan",
                "southdown" : __DIR__"lhqpaifang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
