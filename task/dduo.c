#include <ansi.h> 
inherit TASK; 
void create() 
{
    set_name( HIC "我们的故事" NOR, ({ "our story", "story" }) );  
    set_weight(1); 
    if( clonep() )
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本写着柒叶和多多的爱情故事的书。\n"); 
          } 
    set("owner", "多多"); 
    setup(); 
}
