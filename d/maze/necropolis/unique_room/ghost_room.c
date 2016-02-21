
#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIM "≤–∆∆¡ÈÃ√" NOR);
        set("long", @LONG
≤–∆∆¡ÈÃ√£°
LONG);
        
        set("maze", 1);
        set("no_clean_up", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("outdoors", "necropolis");
        
        set("objects",([
	        "/d/maze/necropolis/npc/ghost": 5,   
	        "/d/maze/necropolis/npc/ghost_fire": 2,    
	        "/d/maze/necropolis/npc/ghost_eye": 2,  
                "/d/maze/necropolis/npc/ghost_devil": 1,  
        ]));
        setup();
        // replace_program(ROOM);
}
