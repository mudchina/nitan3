//   panlong.c 盘龙式
//   looo/2001/6/21
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int bs;
        int damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail(" 盘龙式只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
 return notify_fail("你必须空手才能使用盘龙式\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的内功的修为不够,不敢贸然使用盘龙式。\n");

        if (me->query_skill("longxiang", 1) < 150)
                return notify_fail("你的龙象般若功不够娴熟，不敢贸然使用盘龙式。\n");

        if (me->query("max_neili") < 1500)
                return notify_fail("你的内力不够，不敢贸然使用盘龙式。\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你的内力不足，无法施展盘龙式。\n");
        if (me->query_skill_mapped("force") != "longxiang")
                return notify_fail("你没有激发龙象般若功，不敢贸然使用盘龙式。\n");

        msg = HIC "$N" HIC "凌空跃起，巨臂一震，正是龙象般若功的绝技--盘龙式！\n"
              HIC "隐若可见无数股内家气旋配合掌劲，直逼" HIC "$n" HIC "而去 \n"NOR;

        ap = me->query_skill("longxiang") + me->query("str") * 10;


 if (random(me->query_skill("force")) > target->query_skill("force")/3 || !living(target))
        {
                damage = ap + 500;
                bs = 3;
                me->add("neili", -450);
                me->start_busy(bs);


         msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                       HIR "结果" HIR "$n" HIR "被" HIR "$N" HIR "的气势所摄，一惊之下，竟然忘了抵挡！掌劲硬生生透身而过！！\n"NOR);
        } else

        {

                me->start_busy(4);
                msg += HIY "$n" HIY "暗叫厉害，来不及细想，一个翻身，后退数步！避了这鬼神一击\n"NOR;
        }
                message_combatd(msg, me, target);

                return 1;
}

