// jingshen.c 六脉惊神
// looo/2001/6/28
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int skill, skill2;

        int i;
        i = me->query_skill("six-finger", 1) - 50;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「六脉惊神」只能对战斗中的对手使用。\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("你没有激发六脉神剑，无法施展「六脉惊神」。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你没有准备使用六脉神剑，无法施展「六脉惊神」。\n");

        skill = me->query_skill("six-finger", 1);
        skill2 = me->query_skill("yiyang-zhi", 1);
        if (skill < 200)
                return notify_fail("你的六脉神剑修为有限，无法使用「六脉惊神」！\n");

        if (skill2 < 200)
                return notify_fail("你的一阳指修为有限，无法使用「六脉惊神」！\n");

        if (me->query_skill("force") < 400)
                return notify_fail("你的内功火候不够，难以施展「六脉惊神」！\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("你的内力修为没有达到那个境界，无法运转内力形成「六脉惊神」！\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须是空手才能施展「六脉惊神」！\n");

        if (me->query("neili") < 500)
                return notify_fail("你的真气不够，现在无法施展「六脉惊神」！\n");

        msg = HIY "$N" HIY "十指连动，忽伸忽缩，或点或按，空中气流激荡，剑气自"
              HIY "$N" HIY "指中汹涌而出，惊震四方！！\n"
              HIR "六剑连出，剑气回荡，直割得$n眉毛削落，脸面生通，再也不能前进半分！\n" NOR;
             message_vision(msg, me,target);

        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", 250);
        {
        msg =  HIC "-------------------------少冲剑 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIW "-------------------------少泽剑 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIY "------------------------ 中冲剑 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIG "-------------------------关冲剑 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIM "-------------------------商阳剑 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


        msg =  HIR "-------------------------少商剑 \n"NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

        }
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/damage", -250);
        me->add("neili",-800);
        me->start_busy(4);
        return 1;
}
