// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// qian.c

#include <ansi.h>
#include <combat.h>

#define QIAN "��" HIR "Ǭ������" NOR "��"

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/wuliang-jian/qian"))
                return notify_fail("�㻹���˽�������е��˹����ţ��޷�ʩչ" QIAN "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" QIAN "��\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" QIAN "��\n");

        if (me->query_skill("wuliang-jian", 1) < 100)
                return notify_fail("�������������Ϊ����������ʩչ" QIAN "��\n");

        if (me->query("neili") < 300)
                return notify_fail("�����������������ʩչ" QIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "ֻ��$N" HIR "����" + weapon->name() + HIR "���"
              "��ৡ������Ľ�������ȥ�Ƽ��죬ȫȻ����$n" HIR "��\n" NOR;

        ap = ap_power(me, "sword");
        dp = dp_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = da_power(me, "sword");
                me->add("neili", -150);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "���$n" HIR "�赲��������ʱ��$N"
                                           HIR "ն���������˿ڼ��ǣ��಻���ԡ�\n"
                                           NOR);
        } else
        {
                me->add("neili", -50);
                me->start_busy(3);
                msg += CYN "��ȴ��" CYN "$n" CYN "�͵İεض��𣬱ܿ���"
                       CYN "$N" CYN "�Ľ��С�\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
