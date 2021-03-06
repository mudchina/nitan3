#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(RED "帝之宝石" NOR, ({ "RED jewel4","jewel4" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "一块闪烁这奇异光芒的红色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 140000);
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


                        "str" : 4,           // 增加膂力
                        "dex" : 4,           // 增加根骨

                        ////////////////////     兵器特有属性

                        "attack" : 45,        // 攻击等级：+45
                        "damage" : 45,        // 兵器伤害：+45
                        "fire_attack"   : 45, // 火焰攻击
                        "perferm_ap"    : 5,   // 绝招命中：+5%
                        "add_damage"    : 3, // 追加伤害2%

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "str" : 4,            // 增加膂力
                        "dex" : 4,            // 增加根骨
                        ////////////////////     防具特有属性

                        "reduce_fire"   : 30, // 化解火焰：30%
                        "reduce_damage" : 30, // 化解伤害：30%
                        "max_neili"     : 10, // 内力上限：+10%
                        "perform_dp"    : 4,  // 绝招防御：+4%

                        "qi_recover_speed"     : 12, // 气血恢复速度：+12%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}


