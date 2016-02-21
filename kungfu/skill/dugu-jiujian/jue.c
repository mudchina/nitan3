// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// jue.c 「总诀式」

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon;
        int skill, jing_cost;
        int improve;

        skill = me->query_skill("dugu-jiujian", 1);
        jing_cost = 45 - (int)me->query("int");
        if (jing_cost < 5) jing_cost = 5;

        /*
	if (environment(me)->query("no_fight"))
		return notify_fail("这里太嘈杂，你不能静下心来演练。\n");
        */

        if (me->is_fighting())
                return notify_fail("「总诀式」不能在战斗中演练。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你必须先去找一把剑。\n");

        if (! skill || skill < 20)
                return notify_fail("你的独孤九剑等级不够, 不能演练「总诀式」！\n");

        if (me->query("neili") < 50)
                return notify_fail("你的内力不够，没有力气演练「总诀式」！\n");

        if (me->query("jing") < -jing_cost)
                return notify_fail("你现在太累了，无法集中精神演练「总诀式」！\n");

        if (me->query_skill("dugu-jiujian", 1) > 800 && 
            me->query_skill("dugu-jiujian", 1) > me->query_skill("sword", 1))
                return notify_fail("你的剑法不够，无法使用「总诀式」来提高独孤九剑！\n");

        if (! me->can_improve_skill("dugu-jiujian"))
                return notify_fail("你的实战经验不够，无法体会「总诀式」！\n");

        msg = HIG "$N" HIG "使出独孤九剑之「总诀式」，将手中" +
              weapon->name() + HIG "随意挥舞击刺。\n" NOR;
        message_combatd(msg, me);

        me->add("neili", -50);
        me->receive_damage("jing", jing_cost);

        if (skill < 60)
           improve = 10; else
        if (skill < 90)
           improve = 10 + random((int)me->query_int() - 9); else
        if (skill < 140)
           improve = 10 + random((int)me->query_int() * 2 - 9); else
        if (skill < 200)
           improve = 10 + random((int)me->query_int() * 4 - 9); else
           improve = 10 + random((int)me->query_int() * 8 - 9);

        tell_object(me, MAG "你的「基本剑法」和「独孤九剑」进步了！\n" NOR);
        me->improve_skill("sword", improve);
        me->improve_skill("dugu-jiujian", improve * 3 / 2);
        me->start_busy(random(2));
        return 1;
}
