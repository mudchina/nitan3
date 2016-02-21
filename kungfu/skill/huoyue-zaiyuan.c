inherit SKILL;

mapping *action = ({
([      "action" : "$N使出「或跃在渊」，向$n的$l连拍数掌",
        "dodge"  : 20,
        "parry"  : 15,
        "force"  : 210,
        "damage" : 80,
        "damage_type": "震伤"
]),
});

string main_skill()
{
        return "xianglong-zhang";
}

int valid_enable(string usage)
{
        return usage == "strike";
}

int valid_learn(object me)
{
        if (me->query_skill("xianglong-zhang", 1) > 0)
                return notify_fail("你已经学全十八掌了，不必再单独学习。\n");

        if ((int)me->query("str") < 31)
                return notify_fail("你的先天膂力孱弱，难以修炼降龙十八掌。\n");

        if ((int)me->query("con") < 24)
                return notify_fail("你的先天根骨孱弱，难以修炼降龙十八掌。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，难以修炼降龙十八掌。\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("你的内力修为不足，难以修炼降龙十八掌。\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法火候不够，难以修炼降龙十八掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("huoyue-zaiyuan", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的降龙十八掌。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 120)
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 50)
                return notify_fail("你的内力不够练降龙十八掌。\n");

        me->receive_damage("qi", 100);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huoyue-zaiyuan/" + action;
}
