// bibo-shengong.c 碧波神功
// By Jungu
#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("bibo-shengong", 1);
    return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_force(string force)
{
    return 1;
    return (force == "luoying-xinfa");
}

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("bibo-shengong", 1);

	if (me->query("gender") == "无性" && lvl > 49)
		return notify_fail("你无根无性，阴阳不调，难"
                                   "以领会高深的碧波神功。\n");

/*
        if (me->query_skill("chuixiao-jifa", 1) < 100)
                return notify_fail("你没有精通吹箫技法，无法"
                                   "领会碧波神功的奥秘。\n");
*/

	return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("碧波神功只能用学的，或是从运用(exert)中增加熟练度。\n");
}

string exert_function_file(string func)
{
    return __DIR__"bibo-shengong/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short"	:me->name()+"正踏著八卦方位缓步行走疗伤。",
"start_self"    :HIY"你运气凝神，脚下缓缓踏起八卦方位，开始运用碧波神功调理伤势。\n"NOR,
"on_self"   :HIG"你脚下缓缓踏著八卦方位，步法暗合五行九宫，一边潜运碧波神功调理伤势。\n"NOR,
"start_other"	:HIG""+me->name()+"缓步走动，呼吸由急促渐渐转而悠长，面上青气时隐时现。\n"NOR,
"finish_self"	:HIY"你缓步行走多时，自觉经脉顺畅，内伤尽去，在东方乙木之位停下了步伐。\n"NOR,
"finish_other"	:me->name()+"疗伤已毕，脸上青气一闪而退，停下脚步，看上去气色饱满，精神抖擞。\n",
"unfinish_self"	:"你正以奇门步法调匀真气，忽觉内息後继乏力，祗得停下脚步，暂缓疗伤。\n",
"unfinish_other":me->name()+"停下脚步，脸上青气隐退，气色看起来好多了。\n",
"halt_self"	:"你吐气纳息，硬生生地将内息压了下去，停下了脚步。\n",
"halt_other"	:me->name() +"缓缓停下步伐，身子一震，吐出一口瘀血，脸上青气随之散逸。\n",
"dazuo"		:"你闭上眼睛，脚踏八卦，步合五宫，耳中潮起潮落，内息渐长。\n",
"tuna"		:"你缓缓地呼吸，胸中似有大海浪潮汹涌彭湃，脑中却宁静一片，精神振奋。\n",
        ]);
}
