#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, skill;
        string msg;

        if (! target) target = offensive_target(me);
        skill = me->query_skill("shenghuo-ling",1);
        if (!objectp(weapon = me->query_temp("weapon")))
           return notify_fail("你使用的兵器不对，不能使用圣火令之光华令！\n");

        if( !(me->is_fighting() ))
            return notify_fail("光华令只能对战斗中的对手使用。\n");

        if( skill < 140)
            return notify_fail("你的圣火令法等级不够, 不能使用光华令！\n");

        /*
	if( me->query_skill_mapped("force") != "shenghuo-xuanming")
	    return notify_fail("你使用的内功并非圣火玄冥，无法使用圣火令法！\n");
        */

        if( me->query("max_neili") < 1200 )
            return notify_fail("你的内力修为不足，无法运用光华令！\n");

        if( me->query("neili") < 800 )
            return notify_fail("你的内力不够，无法使用光华令！\n");
                        
        msg = HIY "$N猛吸一口气，使出圣火令法之光华令，手中" +weapon->name()+ NOR + HIY"御驾如飞，幻出无数道金芒，将$n笼罩起来！\n" NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 || !living(target))
        {
            damage = (int)me->query_skill("force");
            damage += random(damage/2);
	    damage += me->query("jiali");
            me->add("neili", -damage/2);
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
            HIR "$n只觉对方劲道铺天盖地般袭来，来势汹涌，完全无法阻挡。顿时只感全身几处刺痛，鲜血飞溅而出！\n" NOR);

            me->start_busy(2);
        } else
        {
            msg += CYN "可是$n看准$N的破绽，猛地向前一跃，跳出了$N的攻击范围。\n"NOR;
            me->add("neili", -200);
            me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}


