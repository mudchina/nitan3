// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// bafang.c 威镇八方
         
#include <ansi.h>
#include <combat.h> 
         
inherit F_SSERVER; 
#include <balance.h>
         
int perform(object me, object target) 
{ 
        object weapon; 
        string msg; 
        int ap, dp; 
        int damage; 

        if (userp(me) && ! me->query("can_perform/shenzhang-bada/bafang"))
                return notify_fail("你还没有受过高人指点，无法施展「威镇八方」。\n");
                        
        if (! target) target = offensive_target(me); 
        
        if (! target || ! me->is_fighting(target)) 
                return notify_fail("「威镇八方」只能在战斗中对对手使用。\n"); 
         
        if (me->query_temp("weapon") || 
            me->query_temp("secondary_weapon")) 
                return notify_fail("你必须空手才能使用「威镇八方」！\n"); 
         
        if (me->query_skill("force") < 300) 
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n"); 
        
        if (me->query_skill("shenzhang-bada", 1) < 200) 
                return notify_fail("你的神掌八打修为不够，目前不能使用「威镇八方」！\n"); 
         
        if (me->query("neili") < 700) 
                return notify_fail("你的真气不够，无法使用「威镇八方」！\n"); 
         
        if (me->query_skill_mapped("strike") != "shenzhang-bada") 
                return notify_fail("你没有激发神掌八打，不能使用「威镇八方」！\n"); 
         
        msg = HIY "$N" HIY "深深的吸了一口气，大喝一声，全身衣袍无风自鼓，" 
                   HIY "然后提气往上一纵，居高临下，双掌奋力击下，刹那间，内劲犹如旋风般"
                   "击向$n" + HIY "！\n" NOR; 
         
        ap = ap_power(me, "strike") + me->query("str") * 20;
        dp = dp_power(target, "parry") + target->query("dex") * 20;
        
        if (ap / 2 + random(ap) > dp)
        { 
                damage = da_power(me, "strike");
                me->add("neili", -350); 
         
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70); 
        } else 
        { 
                me->add("neili", -100); 
                me->start_busy(3); 
                msg += CYN "可是$p" CYN "看破了$N" CYN "的企图，轻轻" 
                       CYN "向后飘出数丈，躲过了这一致命的一击！\n"NOR; 
        } 
        message_combatd(msg, me, target); 
         
        return 1; 
}
