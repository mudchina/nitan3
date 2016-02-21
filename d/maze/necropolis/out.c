inherit ROOM; 

void create() 
{ 
        set("short", "墓园出口"); 
        set("long", @LONG 
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG
); 
			
        set("outdoors", "necropolis"); 
        set("virtual_room", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
	        "north":__DIR__"maze/exit",
                "out"  : "/d/shaolin/xiaojing1",
        ])); 
			
        setup();

} 
int valid_leave(object me, string dir)
{
	object *inv, obj;
        if (dir == "out")
        {
    	        tell_object(me, "check!\n");
    	        inv = all_inventory(me);
    	        if (inv && sizeof(inv)>0)
		    	foreach(obj in inv) {
		    		if (obj && obj->query("maze_item"))
		    		        destruct(obj);
		    	}
        }
        return 1;
}
