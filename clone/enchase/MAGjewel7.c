#include <ansi.h>
inherit ITEM;
int is_enchase_ob() { return 1; }
void create()
{
        set_name(MAG "神之宝石" NOR, ({ "MAG jewel7","jewel7" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "一块闪烁这奇异光芒的紫色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 200000);
                set("no_identify", 1);		
		set("can_be_enchased", 1);
		
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                
                set("enchase/SN", 6);
                set("magic/type", "magic"); 
                set("magic/power", 15 + random(16));    
                set("magic/cur_firm", 90);  // 抗磨损度
                set("magic/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "con" : 10,           // 增加身法

                        ////////////////////     兵器特有属性

                        "perferm_ap"    : 10,  // 绝招命中：+10%
                        "suck_eff_jing" : 30, // 伤敌精力上限
                        "suck_jingli"   : 30, // 吸取精力
                        "suck_neili"    : 30, // 吸取内力

                   ]));

                set("magic/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "con" : 10,           // 增加身法

                        ////////////////////     防具特有属性

                        "defense": 100,       // 防御等级：+100
                        "armor"  : 100,       // 防御能力：+100
                        "perform_dp"    : 10,  // 绝招防御：+10%
                        "reduce_damage" : 50, // 化解伤害：50%
                        "reduce_busy"   : 50, // 化解忙乱：50%

                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}



