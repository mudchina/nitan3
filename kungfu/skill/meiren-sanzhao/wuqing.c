// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage, ap, dp;

        if (userp(me) && ! me->query("can_perform/meiren-sanzhao/wuqing")) 
                return notify_fail("你还没有受过高人指点，无法施展「玉女无情」。\n"); 

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("玉女无情只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展玉女无情。\n");

        if( (int)me->query_skill("sword", 1) < 120 )
                return notify_fail("你的基本剑法级别不够，不会使用玉女无情。\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("你的内功还未娴熟，不能用玉女无情。\n");

        if( (int)me->query("neili", 1) < 400 )
                return notify_fail("你现在内力太弱，不能使用玉女无情。\n");

        msg = HIB "\n\n$N真气催动，带得剑意纵横无情！\n" NOR;
        msg += HIY "\n$N右手支颐，左袖轻轻挥出，长叹一声，脸现寂寥之意，无奈中使出杀招。\n\n" NOR;
        
        ap = ap_power(me, "sword"); 
        dp = dp_power(target, "dodge"); 
             
        if (ap / 2 + random(ap) > dp)
        {
                damage = da_power(me, "sword");         
                me->add("neili", -300);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "只听砰、砰、砰三声响，$n身上被了几个窟窿，鲜血狂喷。\n" NOR);
                me->start_busy(2+random(2));
        }
        else 
        {
                msg += HIG"$p灵光一现，纵身跃起，本能的反应帮$p逃过此劫。\n\n"NOR;
                me->add("neili", -100);
                me->start_busy(2);       
        }

        message_combatd(msg, me, target);
        return 1;
}

