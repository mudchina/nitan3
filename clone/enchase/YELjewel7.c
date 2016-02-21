#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(YEL "神之宝石" NOR, ({ "YEL jewel7","jewel7" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "一块闪烁这奇异光芒的黄色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 200000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                
                set("enchase/SN", 1);    
                set("can_be_enchased", 1);    // 只有最高等级的宝石才有此标志
		set("magic/type", "magic"); 
		set("magic/power", 15 + random(16)); 
                set("magic/cur_firm", 90);  // 抗磨损度
                set("magic/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "con" : 10,           // 增加身法

                        ////////////////////     兵器特有属性

                        "busy_time"     : 4,  // 忙乱敌人4秒
                        "unarmed_damage": 90, // 手法伤害：+90
                        "no_exert"      : 4,  // 内息紊乱4秒

                   ]));

                set("magic/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "con" : 10,           // 增加身法

                        ////////////////////     防具特有属性

                        "avoid_poison"  : 90, // 毒性回避：90%
                        "dodge"  : 100,       // 轻功等级：+100
                        "reduce_busy"   : 50, // 化解忙乱：50%

                        "jingli_recover_speed" : 20, // 精力恢复速度：+20%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}


