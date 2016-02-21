//hongtianza.c ¶áÃüÈı¸«Ö®¡¸ºäÌìÔÒ¡¹
// Modified by Venus Oct.1997
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    string msg,*limbs;
    int i,size,damage;
    object my_w,target_w;
    my_w = me->query_temp("weapon");
    target_w = target->query_temp("weapon");
    if( !target ) target = offensive_target(me);


    if( target->is_busy() )
    return notify_fail(target->name() + "Ä¿Ç°ÕıÃ£È»²»ÖªËù´ë£¬¼Ó½ô¹¥»÷°É¡£\n"
);
    if( (int)me->query_skill("duanyun-fu",1) < 50)
    return notify_fail("ÄãÄ¿Ç°¹¦Á¦»¹Ê¹²»³ö¡¸ºäÌìÔÒ¡¹¡£\n");
    if( (int)me->query("neili") < 100 )
    return notify_fail("ÄãµÄÄÚÁ¦²»¹»¡£\n");
    me->add("neili", -60);
msg = CYN"$NÍ»È»±©ºğÒ»Éù£º¡°ÎÒÔÒ£¡ÎÒÔÒ£¡ÎÒÔÒÔÒÔÒ£¡¡±£¬ÊÖÖĞ¾Ş¸«¾¹È»ÔÒÏò$pÊÖÖĞ±øÈĞ£¡\n"NOR;
    me->start_busy(1);

    if (target->query_temp("weapon") ||
   target->query_temp("secondary_weapon")) {

    if( random(me->query("combat_exp")) >
   (int)target->query("combat_exp")/3 ) {
    if( target_w->weight() > 2 * random(my_w->weight()) ) {
msg += "½á¹û$pÊÖÖĞµÄ"+target_w->query("name")+"±»$PµÄºäÌìÔÒÔÒ¸öÕı×Å£¬ÔÙÒ²°ÑÎÕ²»×
×¡£¬Á¢¼´ÍÑÊÖ·É³ö£¡\n" NOR;
    target_w->unequip();
    target_w->move(environment(target));
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
}
   msg += HIC
"Ö»¼û$nÊÖÖĞµÄ"+target_w->query("name")+"¾¹È»±»ÔÒ¶Ï×÷Êı¶Î£¬²¢ÇÒ
ÊÜµ½$NµÄ¾¢ÆøµÄ¼¤µ´¶øÏò$nÑ¸ËÙÉäÈ¥£¡\n"NOR;
    message_combatd(msg,me,target);
    target_w->unequip();
    target_w->move(environment(target));
    target_w->set("name", target_w->query("name") + "µÄËéÆ¬");
    target_w->set("value", target_w->query("value")/10);
    target_w->set("weapon_prop", 0);
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
    limbs=target->query("limbs");
    me->start_busy(1);
    msg += "½á¹û$p´ôÁ¢µ±³¡£¬±»¹¥ÁË¸ö´ëÊÖ²»¼°£¡\n" NOR;
    size=(int)(me->query_skill("duanyun-fu")/10);
    damage=random(size)+size;
damage=damage+me->query_str()/3+random(me->query_temp("apply/damage"));
    for(i=0;i<=random(size);i++)
   {
   msg =HIB"¡°àÍ¡±£¬ËéÆ¬ÉäÈë$p"+limbs[random(sizeof(limbs))]+"£¡\n"NOR;
   message_combatd(msg,me,target);
   target->receive_damage("qi",damage,me);
   target->receive_wound("qi",damage/3,me);
   }
    COMBAT_D->report_status(target);
    } else {
    msg += "¿ÉÊÇ$p¼±Ã¦½«×Ô¼ºµÄ±øÈĞÉÁ¿ª£¬²¢Ã»ÓĞÈÃ$PµÄ¼ÆÄ±µÃ³Ñ¡£\n" NOR;
    }
    return 1;
    }
    return notify_fail(target->name() + "Ä¿Ç°ÊÇ¿ÕÊÖ£¬ÄãÏëÔÒÊ²Ã´£¿\n");
}

