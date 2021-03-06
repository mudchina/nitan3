// Created by Lonely
// taiji-shengong.c 太极神功

#include <ansi.h>

inherit FORCE;

int valid_force(string force) { return 1; }       

int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("taiji-shengong", 1); 
        return lvl * lvl * 22 * 15 / 100 / 200; 
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("taiji-shengong", 1);


        if (me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的太极神功。\n");

        if (me->query("class") == "bonze" )
                return notify_fail("太极神功讲究阴阳调合，有违佛家六根清净之意，"
                        + RANK_D->query_respect(me) + "欲修此功，已是罪过。\n");

        if (lvl > 10 && (int)me->query("shen") < lvl * 100
             && me->query_skill("taoism", 1) < 100) 
                return notify_fail("你的侠义正气太低了。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("太极神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"taiji-shengong/" + func;
}


mapping curing_msg(object me)
{
        return ([
                "apply_short"   : "坐在一旁垂帘入定，头顶笼罩氤氲白气，汗气上蒸。",
                "start_self"    : "潜运内力，在周身穴道流转疗伤，调匀气息。\n",
                "start_other"   : "闭目坐下，片刻之时，头顶冒出丝丝白气。\n",
                "finish_self"   : "只觉内息运转顺畅，将真气还合丹田，站起身来。\n",
                "finish_other"  : "惨白的脸色渐渐红润，缓缓睁开眼，站起身来。\n",
                "unfinish_self" : "渐感真气不纯，后劲不继，不得不将在体内搬运的内息收回。\n",
                "unfinish_other": me->query("eff_qi") < me->query("max_qi") * 3 / 4 ?
                                  "猛地里口一张，喷出几口鲜血。\n" :
                                  "猛地里口一张，吐出口紫黑瘀血。\n",
        ]);
}

                

