// Copyright (C) 2003, by Xlz. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// yuchang-sword.c 鱼肠剑
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create()  
{  
        set_name(HIY "鱼肠剑" NOR, ({"yuchang sword", "yuchang", "sword"}));  
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {  
        set("unit", "把");  
                        set("long", sort_msg(CYN "" 
                                     ""
                                     ""
                                     ""
                                     ""
                                     "\n" NOR)); 
        set("value", 100000);  
        set("material", "steel"); 
        set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？");  
        set("unique", 1);  
        set("rigidity", 500);  
        set("replica_ob", "/clone/weapon/changjian"); 
        set("no_put",1);  
        set("no_steal",1);    
        set("wield_msg",CYN"$N[噌]的一声抽出一把轩辕夏禹，漫天乌云，杀气四溅。\n"NOR);  
        set("unwield_msg",CYN"$N把手中的轩辕夏禹插入剑鞘，乌云速散，杀气顿无。\n"NOR);  
     }
     init_sword(650); 
     setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing", me->query("str") * 2, me); 
        victim->receive_wound("jing", me->query("str") * 2, me); 
         return CYN "轩辕夏禹夹带着刺耳的破空声划出一道道长虹，霎时间$n" 
               CYN "只感到心神意乱。\n" NOR; 
}
