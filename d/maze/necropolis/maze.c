// write by starfish

#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X	0
#define ENTER_ROOM_Y    0
#define ENTER_ROOM_Z    0

void create() 
{ 
        // 迷宫房间所继承的物件的档案名称。 
        set_inherit_room( ROOM );  
			
        //唯一房间
        set_unique_room( ({
                "/d/maze/necropolis/unique_room/skeleton_room",
                "/d/maze/necropolis/unique_room/ghost_room",
                "/d/maze/necropolis/unique_room/zombie_room",
                "/d/maze/necropolis/unique_room/rest_room",
                "/d/maze/necropolis/unique_room/quest_room",
        }) ); 

        //迷宫房间里的怪物。 
        set_maze_npcs( ([
                "/d/maze/necropolis/npc/skeleton": 1+random(2),  
                "/d/maze/necropolis/npc/skeleton_fighter": 1,
                "/d/maze/necropolis/npc/skeleton_mage": 1,
                "/d/maze/necropolis/npc/zombie": 1+random(2),  
                "/d/maze/necropolis/npc/zombie_blood": 1,
                "/d/maze/necropolis/npc/zombie_power": 1,
                "/d/maze/necropolis/npc/ghost": 1+random(2),  
                "/d/maze/necropolis/npc/ghost_fire": 1,
                "/d/maze/necropolis/npc/ghost_eye": 1,
        ]) );	
	//不算死亡		
        //set_no_death_room(1);
        
        //迷宫的单边长 
        set_maze_long(8); 
			
        //入口方向(出口在对面) 
        set_entry_dir("north"); 
			
        //入口与区域的连接方向 
        set_link_entry_dir("north"); 
			
        //入口与区域的连接档案名 
        set_link_entry_room(__DIR__"enter"); 
			
        //出口与区域的连接方向 
        set_link_exit_dir("south"); 
			
        //出口与区域的连接档案名 
        set_link_exit_room(__DIR__"out"); 
			
        //以下是入口坐标
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
			
        //普通房间描述
        set_maze_room_short(RED "诡异墓园" NOR);
			
        set_maze_room_desc(@LONG
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG); 
			
        //入口房间短描述 
        set_entry_short(HIR "诡异墓园入口" NOR); 
			
        //入口房间描述 
        set_entry_desc(@LONG
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG); 
			
        //出口房间短描述 
        set_exit_short(HIW "诡异墓园出口" NOR); 
			
        //出口房间描述 
        set_exit_desc(@LONG
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG); 

        // 迷宫房间是否为户外房间？ 
        set_outdoors(1); 
						
} 

string query_my_map(){  return read_file(__DIR__"maze.map");}
