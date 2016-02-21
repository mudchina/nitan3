// zhen.c 猴拳「震」字诀
// by Lonely

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg, pmsg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("神功震敌只能对战斗中的对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「震」字诀！\n");         
                
        if( (int)me->query_skill("mizong-houquan", 1) < 40 )
                return notify_fail("你的猴拳不够娴熟，不会使用「震」字诀。\n");
                                
        if( (int)me->query("neili", 1) < 200 )
                return notify_fail("你现在内力太弱，不能使用「震」字诀。\n");
                        
        msg = CYN "$N默运神功，使出猴拳「震」字诀，企图以内力震伤$n。\n"NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 )
        {       
                damage = (int)me->query_skill("force", 1);
                
                damage = 100 + random(damage/2);
                me->add("neili", -200);
                
                if( damage < 20 ) pmsg = HIY"结果$n受到$N的内力反震，闷哼一声。\n"NOR;
                else if( damage < 40 ) pmsg = HIY"结果$n被$N以内力反震，「嘿」地一声退了两步。\n"NOR;
                else if( damage < 80 ) pmsg = RED"结果$n被$N以内力一震，胸口有如受到一记重锤，连退了五六步！\n"NOR;
                else pmsg += HIR"结果$n被$N的内力一震，眼前一黑，身子向后飞出丈许！！\n"NOR;
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30, pmsg);
                
                me->start_busy(3);
                if (! target->is_busy())
                        target->start_busy(random(3));
                
        } else 
        {
                me->add("neili", -50);
                me->start_busy(3);
                msg += CYN"可是$p看破了$P的企图，并没有上当。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

