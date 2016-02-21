// yi.c �ٻ�����

#include <ansi.h>
#include <combat.h>

#define YI "��" HIW "�ٻ�����" NOR "��"

inherit F_SSERVER;
#include <balance.h>
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/baihua-cuoquan/yi"))
                return notify_fail("�㻹û���ܵ�����ָ�㣬����������" YI "��\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(YI "ֻ�ܿ���ʩչ��\n");
                
        if (me->query("max_neili") < 3000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" YI "��\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("����ڹ�����㣬�޷�ʹ��" YI "��\n");

        if ((int)me->query_skill("baihua-cuoquan", 1) < 150)
                return notify_fail("��İٻ���ȭ��򲻹����޷�ʹ��" YI "��\n");

        if (me->query_skill_prepared("unarmed") != "baihua-cuoquan")
                return notify_fail("������û��׼��ʹ�ðٻ���ȭ���޷�ʹ��" YI "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("��������������޷�����" YI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "���һ����˫�Ʒ׷ɣ��������м���ӥצ�������ֲ�"
              "ȭ���������ơ�����ȥ��\n�����ƣ��ջ�ʱ����̫��ȭ������ӳ£�"
              "���޹��ɣ�����ǵ���$n" HIW "��ӿ��ȥ��\n\n" NOR;

        ap = ap_power(me, "unarmed") + me->query("str") * 10;;
        dp = dp_power(target, "parry") + target->query("dex") * 10;

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 12;
                msg += HIR "$n" HIR "ֻ��$P" HIR "��ȭ�籼����ȭ�ͷ׵ݳ���"
                       "�ٸ�ͷ��Ŀѣ����֪����εֵ���\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "ֻ��$p" HIY "��ȭ�籼����ȭ�ͷ׵ݳ���"
                       "��æ����������ǿ�ֵ���\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -300);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(6));
        me->add_temp("apply/attack", -count);

        return 1;
}
