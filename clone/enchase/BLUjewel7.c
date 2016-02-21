#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(BLU "神之宝石" NOR, ({ "BLU jewel7","jewel7" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", BLU "一块闪烁这奇异光芒的蓝色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 200000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                
                set("enchase/SN", 3);    
                set("can_be_enchased", 1);    // 只有最高等级的宝石才有此标志
		set("magic/type", "magic"); 
		set("magic/power", 15 + random(16)); 
                set("magic/cur_firm", 90);  // 抗磨损度
                set("magic/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                            "kar" : 10,           // 增加福源

                        ////////////////////     兵器特有属性

                            "light_attack"  : 100, // 闪电攻击
                            "add_damage"    : 20, // 追加伤害20%
                            "suck_eff_qi"   : 30, // 伤敌气血上限

                   ]));

                set("magic/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                            "kar" : 10,           // 增加福源

                        ////////////////////     防具特有属性

                            "reduce_light"  : 100, // 化解闪电：100%
                            "avoid_poison"  : 100, // 毒性回避：100%
                            "reduce_damage" : 50, // 化解伤害：50%

                            "qi_recover_speed"     : 50, // 气血恢复速度：+50%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}

