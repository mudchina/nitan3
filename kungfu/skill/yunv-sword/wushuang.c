// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// wushuang.c 玉女剑法 无双无对

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me, object target)
{
	object weapon;
        int damage;
	int skill, ap, dp;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("无双无对只能对战斗中的对手使用。\n");

        if (userp(me) && ! me->query("can_perform/yunv-sword/wushuang"))
                return notify_fail("你还没有受过高人指点，无法施展「无双无对」。\n");
                
	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query_skill("yunv-sword", 1) < 80)
		return notify_fail("你的玉女剑法不够娴熟，不会使用「无双无对」。\n");
	
	if ((int)me->query_skill("force") < 120)
		return notify_fail("你的内功不够娴熟，不会使用「无双无对」。\n");
	
	if ((int)me->query("neili") < 300)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_temp("hsj_wu"))
		return notify_fail("你已经在运功中了。\n");

	msg = HIY "$N" HIY "双手握起" + weapon->name() + HIY
              "，剑芒暴长，一式「无双无对」，驭剑猛烈绝伦地往$n"
              HIY "冲刺！\n"NOR;

        ap = me->query_skill("sword") + me->query("level") * 20 + 
             me->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge") + target->query("level") * 20 + 
             target->query_skill("martial-cognize", 1);

        if (ap * 11 / 20 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = (int)me->query_skill("sword");
                damage += random(damage / 4);
                me->add("neili", -250);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "看到$N" HIR "这一剑妙到毫巅，全然无"
                                           "法抵挡，一愣神之间已经被这一剑刺得鲜血飞溅！" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，向旁一跃，躲了开去。" NOR;
        }

        message_combatd(msg, me, target);
	return 1;
}
