// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define HUA "「" HIW "一气化三清" NOR "」"

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;
        int is_yunv = 0;

        if (userp(me) && ! me->query("can_perform/quanzhen-jian/hua"))
                return notify_fail("你未得高人指点，不知该如何施展" HUA "。\n"); 
                
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你所使用的武器不对，难以施展" HUA "。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 200)
                return notify_fail("你全真剑法不够娴熟，难以施展" HUA "。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("你的先天功不够娴熟，难以施展" HUA "。\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("你没有激发全真剑法，难以施展" HUA "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功，难以施展" HUA "。\n");

        if ((int)me->query("max_neili") < 4500)
                return notify_fail("你的内力修为不够，难以施展" HUA "。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你现在的真气不足，难以施展" HUA "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一声长吟，将内力全然运到剑上，" + weapon->name() +
              HIW "剑脊顿时" HIM "紫芒" HIW "闪耀，化作数道剑气劲逼$n"
              HIW "。\n" NOR;

        ap = ap_power(me, "sword") +
             me->query_skill("force");

        dp = dp_power(target, "parry") +
             target->query_skill("force");

	if (stringp(target->query_skill_mapped("sword")) &&
	    target->query_skill_mapped("sword") == "yunv-jian" &&
            target->query_temp("weapon") &&
            target->query_temp("weapon")->query("skill_type") == "sword")
	{
		dp += target->query_skill("yunv-jian", 1);
		is_yunv = 1;
	}
	
        me->start_busy(3);
        me->add("neili", -200);

        if (ap / 2 + random(ap) > dp)
        {
                damage = da_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "顿时只听$n" HIR "一声惨叫，剑气及"
                                           "身，身上接连射出数道血柱。\n" NOR);
                message_combatd(msg, me, target);

                if (ap / 2 + random(ap) > dp)
                {
                        count = me->query_skill("xiantian-gong", 1) / 2;
                        me->add_temp("apply/attack", count);
                        message_combatd(HIY "$N" HIY "见$n" HIY "在这一击之下破"
                                        "绽迭出，顿时身形前跃，唰唰唰又是三剑。"
                                        "\n" NOR, me, target);

                        for (i = 0; i < 3; i++)
                        {
                                if (! me->is_fighting(target))
                                        break;
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }
                        me->add_temp("apply/attack", -count);
                }
        } else
        {
                me->start_busy(2);
                if (is_yunv)
			msg += CYN "却见$n" CYN "微微一笑，反手一招“玉女剑法”，轻松地档住了$N的剑招。\n" NOR;
		else
                        msg += CYN "可是$n" CYN "看破了$N" CYN "的企图，斜跃避开。\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}
