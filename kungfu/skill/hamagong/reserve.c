// reserve.c 蛤蟆功经脉倒转

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

int exert(object me, object target)
{
	object weapon;
	int skill;
	string msg;

	if ((int)me->query_skill("hamagong", 1) < 80)
		return notify_fail("你的蛤蟆功不够娴熟，不会经脉倒转。\n");

	if ((int)me->query("neili") < 200) 
		return notify_fail("你现在的真气不够。\n");

	if ((int)me->query_temp("hmg_dzjm"))
		return notify_fail("你已经倒转经脉了。\n");

	skill = me->query_skill("hamagong", 1);
	msg = HIB "$N" HIB "忽地双手撑地倒立，逆运经脉，顿时"
              "内息暗生，防御力大增。\n" NOR;
	message_combatd(msg, me);

	me->add_temp("apply/dodge", skill / 2);
	me->set_temp("hmg_dzjm", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

	me->add("neili", -100);
	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("hmg_dzjm"))
        {
        	me->add_temp("apply/dodge", -amount);
        	me->delete_temp("hmg_dzjm");
        	tell_object(me, "你双手一撑，一跃而起，将内力收回丹田。\n");
        }
}
