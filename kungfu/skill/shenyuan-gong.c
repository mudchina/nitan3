#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return 1; }       

int query_neili_improve(object me)   
{
        int lvl;  
        lvl = (int)me->query_skill("shenyuan-gong", 1);  
        return lvl /10 * lvl /10 * 20 * 15 / 10 / 20;  
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("shenyuan-gong", 1);
        if (me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的神元功。\n");
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本内功火候还不够，无法领会神元功。\n");
        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("神元功只能用学(learn)的来增加熟练度。\n");
              
}

string exert_function_file(string func)
{
        return __DIR__"shenyuan-gong/" + func;
}
mapping exercise_msg(object me)
{
        return ([
                "status_msg" : "眼神凌厉，神态极为凝重。",
                "start_my_msg" : "随意一站，双手缓缓抬起，深吸一口气，真气开始在体内运转。\n",
                "start_other_msg" : "随意在那里一站，双手缓缓抬起，眼神开始变的凌厉起来。\n",
                "halt_msg" : "眉头一皱，急速运气，把手放了下来。\n",
                "end_my_msg" : "将真气在体内沿脉络运行了一圈，缓缓纳入丹田，放下手，长吐了一口气。\n",
                "end_other_msg" : "的眼睛慢慢闭上，立刻睁开，把手放下，长吐了一口气。\n"
        ]);
}

