// buddhism.c 禅宗心法
// Modified by Venus Oct.1997

#include <ansi.h>
inherit SKILL;
void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if( (int)me->query("guilty") > 0 )
                return notify_fail("你屡犯僧家数戒，尘俗之心太重，无法修炼禅宗心法。\n");

        return 1;
}

int practice_skill(object me)
{
    return notify_fail("禅宗心法只能靠学(learn)来提高。\n");
}

void skill_improved(object me)
{
        if ((int)me->query_skill("buddhism", 1) == 120 && ! me->query("sl/int"))
        {
                me->add("int", 1);
                me->set("sl/int", 1);
                tell_object(me, HIM "\n你的禅宗心法学有所成，提高了你的智力。\n" NOR);
        }
}


