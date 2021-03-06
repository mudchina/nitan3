// juemi.c 天地绝灭
 
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

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("天地绝灭只能对战斗中的对手使用。\n");
 
	if (me->query_skill("never-defeated", 1) < 120)
		return notify_fail("你的不败神功还不够娴熟，不能使用天地绝灭！\n");

        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("你必须手持兵刃才能施展天地绝灭！\n");
        
        if (me->query_skill_mapped("sword") != "never-defeated") 
                return notify_fail("你现在没有激发不败神功为剑法，难以施展天地绝灭。\n"); 

        if (me->query("neili") < 200)
                return notify_fail("你的内力不够，不能使用天地绝灭！\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIC "$N" HIC "随便走了几步，忽然一荡手中的" + weapon->name() +
              HIC "，迅捷无比的扫向$n" HIC "，变化复杂之极，不可思议！\n" NOR;
 
	ap = ap_power(me, "sword") + me->query("int") * 20;
	dp = dp_power(target, "dodge") + target->query("dex") * 20;

        me->start_busy(2);
        me->add("neili", -50);
        if (ap * 11 / 20 + random(ap) < dp)
        {
		msg += HIG "只见$n" HIG "并不慌张，只是轻轻一闪，就躲过了$N"
	               HIG "这一击！\n"NOR;
        } else
	{
		me->add("neili",-70);
                damage = da_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "连忙格挡，可是这一招实在是鬼神莫"
                                           "测，哪里琢磨得透？登时中了$P" HIR "的重创！\n" NOR);
	}

	message_combatd(msg, me, target);
	return 1;
}
