#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N脸上露出诡异的笑容，隐隐泛出绿色的双掌扫向$n的$l",
        "force" : 180,
        "attack": 49,
        "dodge" : -30,
        "parry" : -37,
        "dmage" : 32,
        "damage_type": "瘀伤"
]),
([      "action": "$N突然身形旋转起来扑向$n，双掌飞舞着拍向$n的$l",
        "force" : 230,
        "attack": 56,
        "dodge" : -22,
        "parry" : -34,
        "dmage" : 47,
        "damage_type": "瘀伤"
]),
([      "action": "$N将毒质运至右手，一招「腐尸毒」阴毒无比地抓向$n的$l",
        "force" : 260,
        "attack": 61,
        "dodge" : -20,
        "parry" : 10,
        "dmage" : 60,
        "damage_type": "瘀伤"
]),
([      "action": "$N一声怪叫，双掌挟着一股腥臭之气拍向$n的$l",
        "force" : 380,
        "attack": 79,
        "dodge" : 17,
        "parry" : 36,
        "dmage" : 65,
        "damage_type": "瘀伤"
]),
([      "action": "$N咬破舌尖，口中喷血，聚集全身的力量击向$n",
        "force" : 420,
        "attack": 81,
        "dodge" : 27,
        "parry" : 21,
        "dmage" : 75,
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "sanyin-zhua";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技不足，无法练抽髓掌。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法练抽髓掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的掌法根基不足，无法练抽髓掌。\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力修为太弱，无法练抽髓掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("choushui-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的抽髓掌法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        if (present("huo yan", environment(me)))
        {
                if (random(me->query_skill("strike")) > 250 && me->query("neili") > 1000) 
                {
                        me->add("neili", -100);
                        return ([
                                "action": BLU "$N神色惨淡，伸手打开发髻，长发下垂，覆在脸上，跟着力咬舌尖，" HIR "一口鲜"
                                "血向火焰中喷去。\n那火焰忽地一暗，" HIW "随即大为明亮，$N猛地身子急旋，如陀"
                                "螺般连转了十多个圈子，\n" HIR "大袖拂动，整个火焰堆陡地拨起，便如一座火墙般向$n压过去" NOR,
                                "force" : 450,
                                "dodge" : 100,
                                "parry" : 100,
                                "weapon": "火焰",
                                "attack": 200,
                                "damage_type": "烧伤"]);
                }
                if (random(me->query_skill("strike")) > 215 &&
                    me->query("neili") > 800) 
                    {
                        me->add("neili", -75);
                        return ([
                                "action": HIG "$N厉声大喝，掌力加盛，绿火突然化作一个" 
                                          HIR "斗大的火球，向$n疾冲过来。\n使力极猛，去势奇快，" 
                                          HIG "只见一碧绿的火球在空中骨碌碌的迅速转动" NOR,
                                "force" : 420,
                                "dodge" : 90,
                                "parry" : 90,
                                "weapon": "火球",
                                "attack": 180,
                                "damage_type": "烧伤"]);
                }
                if (random(me->query_skill("strike")) > 180 &&
                    me->query("neili") > 600) 
                {
                        me->add("neili", -50);
                        return ([
                                "action": HIR "$N衣袖一拂，一股劲气直射入火焰之中，"+HIG+"火焰中又分出一道细细的绿火，便如一根水线般，\n"
                                          HIW "$N衣袖挥动，两股劲风分袭$n左右" NOR,
                                "force" : 400,
                                "dodge" : 80,
                                "parry" : 80,
                                "weapon": HIG "绿火" NOR,
                                "attack": 150,
                                "damage_type": "烧伤"]); 
                }
                if (random(me->query_skill("strike")) > 150 &&
                    me->query("neili") > 500) 
                {
                        me->add("neili", -20);
                        return ([
                                "action": HIR "$N随即左掌斜拍出一道"+HIG+"绿火"+HIR+"向$n射去，声势汹汹，"+HIG+"便似一条绿色长蛇横卧空际，轻轻摆动，\n"
                                          HIR "颜色又是鲜艳，"+BLU+"又是诡异，光芒闪烁不定"+HIG+"照映得$n头脸皆碧"NOR,
                                "force" : 400,
                                "dodge" : 80,
                                "parry" : 80,
                                "weapon": HIG"绿火"NOR,
                                "attack": 120,
                                "damage_type": "烧伤"]); 
                }
                
                if (random(me->query_skill("strike")) > 120 &&
                        me->query("neili") > 400 ) {
                        me->add("neili", -10);
                        return ([
                                "action": HIR "$N突然间双眉往上一竖，右手食指点两点，火焰堆中嗤嗤两声轻响，"+HIG+"爆出几朵火花，犹如流星一般，\n"
                                          "在$N内力摧迫下，分从左右袭向$n，来势迅速之极" NOR,
                                "force" : 400,
                                "dodge" : 80,
                                "parry" : 80,
                                "attack": 100,
                                "weapon": "火花",
                                "damage_type": "烧伤"]);
                }
        }        
        level = (int) me->query_skill("chousui-zhang", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("你的内力不够练抽髓掌。\n");

        me->receive_damage("qi", 65);
        me->add("neili", -55);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chousui-zhang", 1);
        flvl = me->query("jiali");

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xx_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                // 以下是抽髓掌的 perform sandu 中的散毒功能转到这里。
                if (me->query_skill("poison", 1) < 101) 
                        me->set("body_poison", me->query_skill("poison", 1) + 1); 
                if (me->query_skill("poison", 1) > 100) 
                        me->set("body_poison", me->query_skill("poison", 1) + 10); 
                //  散毒结束
                return HIW "$n" HIW "只感一阵极寒从心底升起，看来是中了$N" HIW "掌上的剧毒。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"chousui-zhang/" + action;
}
