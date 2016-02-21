// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define CHI "「" HIR "赤炼神刀" NOR "」"

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i, ap, dp;

        if (userp(me) && ! me->query("can_perform/xuedao-daofa/chi"))
                return notify_fail("你还没有受过高人指点，无法施展" CHI "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHI "只能对战斗中的对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对，难以施展" CHI "。\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你的内功火候不够，难以施展" CHI "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 160)
                return notify_fail("你的血刀大法还不到家，难以施展" CHI "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你没有激发血刀大法为刀法，难以施展" CHI "。\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你的真气不够，难以施展" CHI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "嗔目大喝，手中" + weapon->name() + HIW "一势「"
              HIR "赤炼神刀" HIW "」迸出漫天血光，铺天盖地洒向$n" HIW "。\n" NOR;

        ap = ap_power(me, "blade");
        dp = dp_power(target, "parry");
             
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "霎时间$n" HIR "只觉周围四处杀气弥漫，全身气血翻"
                       "滚，甚难招架。\n" NOR;
                count = me->query_skill("xuedao-daofa", 1) / 4;
        } else
        {
                msg += HIY "霎时间$n" HIY "只觉周围四处杀气弥漫，心底微微一"
                       "惊，连忙奋力招架。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        me->add_temp("apply/attack", count);
        me->add("neili", -150);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(6));
        return 1;
}

