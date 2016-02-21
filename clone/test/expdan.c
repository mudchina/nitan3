// zhenyu.c 镇狱惊天丸

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "经验丹" NOR, ({ "exp dan", "dan" }) );
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一颗龙眼大小的药丸，氤氲扑鼻，一嗅之下便觉心旷\n"
                                "神怡。整个药丸流动着金属般的光泽，入手沉重，在\n"
                                "掌心滑动不停，便似有生命一般。\n" NOR);
                set("value", 500000);
                set("unit", "颗");
               set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        	message_vision(HIW "$N" HIW "一仰脖，吞下了一颗经验丹，只见$P"
                               HIW "浑身一颤，七窍都冒出白烟来。\n" NOR, me);

        	
        
        	me->add("combat_exp", 30000);

        
        return 1;
}

int query_autoload()
{
        return 1;
}
