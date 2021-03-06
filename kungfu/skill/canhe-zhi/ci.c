// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// ci.c 参合一指

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (userp(me) && ! me->query("can_perform/canhe-zhi/ci"))
                return notify_fail("你还没有受过高人指点，无法施展。\n");
                
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「参合一指」只能对战斗中的对手使用。\n");

        skill = me->query_skill("canhe-zhi", 1);

        if (skill < 100)
                return notify_fail("你的参合指修为有限，不能使用「参合一指」！\n");

        if (me->query("neili") < 100)
                return notify_fail("你的真气不够，无法运用「参合一指」！\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("你没有激发参合指, 不能使用「参合一指」！\n");

        msg = HIW "$N" HIW "食指伸出，施展出参合指的精妙招式，一道气流袭向$n"
              HIW "的胸前穴位。\n" NOR;

        ap = ap_power(me, "finger");
        dp = dp_power(target, "parry");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -100);
                me->start_busy(2);
                damage = da_power(me, "finger");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 35,
                                           HIR "$n" HIR "躲避不及，顿时觉得顿觉浑身经"
                                           "脉都是一痛，手里不禁一软。\n" NOR);
        } else
        {
                me->add("neili",-40);
                msg += CYN "可是$n" CYN "看破了$N" CYN "的来路，立刻腾挪躲闪，使$N"
                       CYN "的攻击没有起到作用。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
