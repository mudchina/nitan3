// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// tuwu.c

#include <ansi.h>

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        int skill, ap, dp;
        string msg;
        object weapon;

        if (me->query_temp("jinshe/tuwu"))
                return notify_fail("你才用的金蛇吐雾，没法接着就出招。\n");

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail("金蛇吐雾只能在战斗中使用。\n");

        if (! objectp(weapon = me->query_temp("handing")) ||
            (string)weapon->query("id") != "jinshe zhui" ||
            weapon->query_amount() < 1)
                return notify_fail("你手里没拿金蛇锥，不能使用绝招！\n");

        if ((skill = me->query_skill("jinshe-zhui", 1)) < 100)
                return notify_fail("你的金蛇锥法不够娴熟，不会使用金蛇吐雾。\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你内力不够了。\n");

        weapon->add_amount(-1);

        msg = HIY "$N" HIY "一声轻啸，身形微动，手中金蛇锥竟然向上飞"
              "起绕了个圈，随而迅速袭向$n" HIY "的面前。\n" NOR;

        ap = ap_power(me, "strike");
        dp = dp_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -200);
                target->receive_damage("qi", (int)skill / 3, me);
                target->receive_wound("qi", (int)skill / 3, me);
        
                msg += HIM "只听一阵狂风扫叶般的声响中，$N" HIM "手中的"
                       "金蛇锥闪出夺目的光芒，闪耀得$n" HIM "眼冒金花，"
                       "\n除了眼前一重重的雾气外，$n" HIM
                       "啥也看不见了！\n" NOR;
                message_combatd(msg, me, target);
                me->set_temp("jinshe/tuwu", 1);
                target->set_temp("block_msg/all", 1);
                me->start_call_out((: call_other, __FILE__, "tuwu_end", me, target :),
                                   skill / 30);
        } else
        {
                msg += CYN "$n" CYN "心中暗暗一惊，急忙后"
                       "退，闪开了这枚金蛇锥。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}

void tuwu_end(object me, object target)
{
        if (living(target))
        {
                message_combatd("$N抹了抹满脸的" HIR "鲜血" NOR "，终于睁开了眼。\n",
                                target);
                target->set_temp("block_msg/all", 0);
                write(HIR "你终于抹掉了满脸的鲜血，看到了周围的情景。\n"NOR);
                if (me) me->delete_temp("jinshe/tuwu");
        }

        return;
}
