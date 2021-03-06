// an.c 太极拳「按」字诀
// Modify by haiyan

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, acter, ap, dp, taoism;
        string msg;

        if (! target) target = offensive_target(me);

/*
        if (userp(me) && ! me->query("can_perform/taiji-quan/an")) 
                return notify_fail("你还不会使用「按」字诀。\n"); 
*/

        if (! target || ! me->is_fighting(target))
                return notify_fail("「按」字诀只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用「按」字诀！\n"); 
                
        if ((int)me->query_skill("taiji-quan", 1) < 200)
                return notify_fail("你对太极拳理的理解还不够，不会使用「按」字诀。\n");
                                
        if ((int)me->query("neili", 1) < 300)
                return notify_fail("你现在真气太弱，不能使用「按」字诀。\n");
                        
        msg = HIG "$N" HIG "双拳上下挥动，使出太极拳「按」字诀，$n"
              HIG "感到一股强大的劲力从头顶压落。\n" NOR;

        me->add("neili", -200);

        dp = (target->query_skill("force", 1) +
              target->query_skill("parry", 1) +
              target->query_skill("martial-cognize", 1)) / 3;

        if (me->query("character") == "光明磊落" || me->query("character")=="国土无双" || me->query("character") == "狡黠多变")
               acter = 4;
        else
               acter = 5;

        taoism = me->query_skill("taoism", 1);
        if (taoism > 1000) taoism = 1000;
        
        ap = (me->query_skill("taiji-shengong", 1) +
              me->query_skill("taiji-quan", 1) +
              me->query_skill("martial-cognize", 1) +
              taoism) / acter;

        if (target->is_bad())   ap += ap / 4;

        if (random(ap) > dp / 2 || !living(target))
        {
                me->start_busy(3);
                target->start_busy(random(3));

                damage = ap * 10;

                if (me->query("shen") / 800 > 5000)
                     damage += 5000;
                else
                     damage += me->query("shen") / 800;

                damage /= 2;

                damage += me->query("jiali") * 2;
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 70,
                                           HIY "$n" HIY "登感呼吸不畅，胸闷难当，"
                                           HIY "喉头一甜，狂喷数口"HIR"鲜血"HIY"！\n"
                                           ":内伤@?");
        } else 
        {
                me->start_busy(3);
                msg += HIY "$p" HIY "急运内功，聚劲于外，挺身硬接了$P"
                       HIY "这一招，“砰”的一声巨响，双方各自震退数步！\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

