// Room: /suzhou/xifu-tang.c //举办婚宴所在
// llm 99/07/09

inherit ROOM;
void create()
{
	set("short", "喜福堂");
        set("long", @LONG
这里是迎宾楼的二楼，宽敞地可以摆下三十多张八仙桌，正中挂着大大的红
色喜字，由于常常有人在此举办婚宴，这里的红烛也就长明，地上铺着厚厚的大
红地毯，一派喜气洋洋的景象。你站在楼上眺望，可看见碧波湖水，崇山峻岭。
LONG );
	set("exits", ([
                "down" : "/d/suzhou/yingbin-lou1",
	]));

	set("coor/x", 190);
	set("coor/y", -220);
	set("coor/z", 10);
	setup();
   replace_program(ROOM);
}

