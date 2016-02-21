// milin.c
// Modified by haiyan

inherit ROOM;
 
void create()
{
        set("short", "密林");
        set("long", @LONG
这里是荒岛上的茂密树林，阴森可怖。抬头不见天日。鸟兽蛇虫游荡不穷。
LONG );
        set("no_clean_up", 0);
        set("exits", ([ 
            "east"     : __FILE__,
            "west"     : __FILE__,
            "south"     : __FILE__,
            "north"     : __DIR__"huangdao", 
        ])); 

        set("objects", ([ 
            "/clone/beast/dushe" : 1, 
        ])); 

        setup();
        replace_program(ROOM); 
}

