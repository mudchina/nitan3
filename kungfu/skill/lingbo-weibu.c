#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
        "可是$n侧身一让，$N这一招扑了个空。\n",
        "却见$n足不点地，往旁窜开数尺，躲了开去。\n",
        "$n身形微晃，有惊无险地避开了$N这一招。\n",
        "$n跨出几步，落点怪异莫测，让$N这一招没有发挥任何作用。\n",
        "$n自顾自的走出几步，浑然不理$N出招攻向何处。\n",
        "$N这一招眼看就要击中，可是$n往旁边一让，去点之妙，实在是匪夷所思。\n",
        "$n往前一迈，忽然后退，恰恰避开$N这一招，有惊无险。\n",
});

int valid_enable(string usage) 
{ 
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl > 300) lvl = 300;

       if (me->query("dex") < 21) 
                return notify_fail("你先天身法太差，无法学习凌波微步。\n");

        if (me->query("max_neili") < 3000 + lvl * 20)
                return notify_fail("你试着走了两步，顿觉胸"
                                   "口烦恶之极，看来是内力不济。\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("lingbo-weibu", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("lingbo-weibu", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$n" HIW "身子轻轻晃动，$N" HIW
                                            "眼前顿时出现了无数个$n" HIW "的幻影，令$N"
                                            HIW "完全无法辨出虚实。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" HIW "往旁边歪歪斜斜的迈出一步，却恰"
                                            "好令$N" HIW "的攻击失之毫厘。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "这一招来的好快，然后$n"
                                            HIW "一闪，似乎不费半点力气，却将$N"
                                            HIW "这一招刚好避开。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" HIW "轻轻一跃，已不见了踪影，$N"
                                            HIW "心中大骇，却又见$n" HIW "擦肩奔过，"
                                            "当真令人思索菲仪。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "只见$n" HIY "微微一笑，身子轻轻晃动，"
                                 "顿时出现了无数个$n" HIY "的幻影，可是$N"
                                 HIY "精通易理，将其中虚实辨得清清楚楚。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "往旁边歪歪斜斜的迈出一步，然而$N"
                                 HIY "错步跟随，方位毫厘不差。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "一闪，似乎不费半点力气，却将$N"
                                 HIY "这一招刚好避开，可是$N"
                                 HIY "招中有招，进攻却是不止。\n" NOR;
                        break;
                default:
                        result = HIY "但见$n" HIY "轻轻一跃，已不见了踪影，$N"
                                 HIY "不假思索，反身出招，更是巧妙无方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力太差了，难以练习凌波微步。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够了，无法练习凌波微步。\n");

        me->receive_damage("qi", 65);
        me->add("neili", -65);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingbo-weibu/" + action;
}
void skill_improved(object me)
{
        if (me->query_skill("lingboweibu",1) == 80 && ! me->query("lbwb") 
        &&  me->query_skill("literate", 1) > 80)
        {
                tell_object(me, HIY "$N一步步走下来，只觉的心情舒畅，不知不觉内力有所积累。\n" NOR);
                me->add("max_neili", random(30)+20);
                me->add("lbwb",1);
        }
        if (me->query_skill("lingboweibu", 1) == 120 && me->query("lbwb") == 1 
        &&  me->query_skill("literate", 1) > 100)
        {
                tell_object(me, HIM "$N六十四卦走完，刚好绕了一个大圈，回到原地，精神大振。\n" NOR);
                me->add("max_neili", random(30)+20);
                me->add("lbwb", 1);
        }
        if (me->query_skill("lingboweibu", 1) == 160 && me->query("lbwb") == 2 
        &&  me->query_skill("literate", 1) > 120)
        {
                tell_object(me, CYN "$N越走越快，内息随着步法不住运转，隐隐然自己的内力已经有了提高！\n" NOR);
                me->add("max_neili", random(30)+20);
                me->add("lbwb", 1);
        }
        if (me->query_skill("lingboweibu", 1) == 200 && me->query("lbwb") == 3 
        &&  me->query_skill("literate", 1) > 140)
        {
                message_vision(RED "$N步法娴熟，随意踏出，脚步成圆，只感神清气爽，全身精力弥漫！\n" NOR, me);
                me->add("max_neili", random(30)+20);
                me->add("lbwb", 1);
        }
}
