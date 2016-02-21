// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
	set("short", "池塘");
        set("long", @LONG
一池池水映入你的眼帘，小蓬莱屹然水中，曲折的石桥上架着紫藤花棚。池
东你可以看到曲溪楼、西楼、清风池等小筑，掩映于花木山石之间。池西的山腰
间，桂树丛生。秋日，置身于『闻木樨香轩』，阵阵桂香，沁人心脾。轩下，水
涧两岸叠石重重，你不禁为此景而赞叹不已。
LONG );
	set("outdoors", "suzhou");
	set("exits", ([
		"northeast" : "/d/suzhou/gumujiaohe",
	]));
        set("max_room", 4);
	set("objects", ([
		"/d/suzhou/npc/lady1" : 1,
	]));
	set("coor/x", 160);
	set("coor/y", -250);
	set("coor/z", 0);
	setup();
}

