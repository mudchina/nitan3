#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
  	set ("short", "扬州渡");
  	set ("long", @LONG
这里是通往中州城的渡口，你前面的滚滚长江 (river)浊
流滚滚，万舟竞发。两岸渡船来来往往。向南就是中州府。江
边停着些小船。北边一条小路通往扬州的西门。
LONG);

        set("arrive_room", "/d/zhongzhou/zhongzhoudu");
  	set("exits", ([
  		"north" : "/d/city/ximen",
                "west" : "/d/city/xiaofang",
	]));
        set("objects", ([
                CLASS_D("misc") + "/shipopo" : 1,
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

  	set("outdoors", "city");
        set("coor/x", -10);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
