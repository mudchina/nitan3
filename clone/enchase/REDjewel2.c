#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(RED "宝石" NOR, ({ "RED jewel2","jewel2" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一颗红光闪闪的精美宝石，华丽异常。\n" NOR);
                set("unit", "块");
                set("value", 100000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                    
                set("enchase/type", "all");   // 可镶嵌的道具类型"all"或"sword"或"blade"或"cloth"等
                set("enchase/cur_firm", 90);  // 抗磨损度
                set("enchase/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "str" : 2,           // 增加膂力
                        "dex" : 2,           // 增加根骨

                        ////////////////////     兵器特有属性

                        "attack" : 18,        // 攻击等级：+18
                        "damage" : 18,        // 兵器伤害：+18
                        "fire_attack"   : 18, // 火焰攻击
                        "perferm_ap"    : 1,   // 绝招命中：+1%

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "str" : 2,            // 增加膂力
                        "dex" : 2,            // 增加根骨
                        ////////////////////     防具特有属性

                        "reduce_fire"   : 10, // 化解火焰：10%
                        "reduce_damage" : 10, // 化解伤害：10%
                        "max_neili"     : 4, // 内力上限：+4%
                        "perform_dp"    : 1,  // 绝招防御：+1%

                        "qi_recover_speed"     : 4, // 气血恢复速度：+4%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}


