// shanlu5.c
// Date: Nov.1997 by Venus

inherit BUILD_ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这是一条山间的小道，漫山遍野都是绿油油的茶蓬。农家少女们在欢笑声中
采茶，到此不由得尽忘江湖仇杀，只想久居此地。山路延伸向东西两边，北边就
是龙井，东北边有一条土路。
LONG );
        set("exits", ([
                "westup"   : "/d/hangzhou/shanlu4",
                "northeast": "/d/hangzhou/tulu1",
                "north"    : "/d/hangzhou/longjing",
                "east"     : "/d/hangzhou/yanxiadong",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/caichanu" :2,
        ]));
        set("outdoors", "hangzhou");
        set("max_room", 4);
        setup();
}
