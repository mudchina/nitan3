//liangyi-jian.c Á½ÒÇ½£·¨

#include <ansi.h>

inherit SKILL;  
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([      "name":   "·¨·ÖÐþËØ",
    "action" : "$N½£¼â½£Ã¢±©³¤£¬Ò»ÕÐ¡¸·¨·ÖÐþËØ¡¹£¬ÊÖÖÐ$w×Ô×óÏÂ´ó¿ª´óãØ£¬
Ò»½£ÏòÓÒÉÏÏò$nµÄ$l",
    "force" : 120,
    "dodge" : 20,
    "damage" : 300,
    "lvl" : 0,
    "damage_type" : "´ÌÉË"
]),
([      "name":   "µÀ¾¡ÒõÑô",
    "action" : "$N³¤½£È¦×ª£¬Ò»ÕÐ"+(order[random(13)])+"¡¸µÀ¾¡ÒõÑô¡¹"NOR"£¬ÊÖÖÐ$wÆ½Õ¹ÏÂ´£¬Ò»½£ÇáÇá»®¹ý$nµÄ$l",
    "force" : 120,
    "dodge" : 20,
    "damage" : 280,
    "lvl" : 0,
    "damage_type" : "´ÌÉË"
]),
([      "name":   "Ô¨ÁÙÉîÇ³",
    "action" : "$N³¤½£ÇáÁéÌø¶¯£¬½£ËæÉí³¤£¬ÓÒÊÖ$wÊ¹³öÒ»Ê½"+(order[random(13)])+"¡¸Ô¨ÁÙÉîÇ³¡¹"NOR"´ÌÏò$nµÄ
$l",
    "force" : 140,
    "dodge" : 15,
    "damage" : 350,
    "lvl" : 0,
    "damage_type" : "´ÌÉË"
]),
([      "name":   "Ë®·ºÇà»Æ",
    "action" : "$N³¤½£ÏÂÖ¸£¬½£ÒâÁ÷×ª£¬Ò»ÕÐ"+(order[random(13)])+"¡¸Ë®·ºÇà»Æ¡¹"NOR"Ö±È¡$nµÄ$l",
    "force" : 150,
    "dodge" : 15,
    "damage" : 280,
    "lvl" : 0,
    "damage_type" : "´ÌÉË"
]),
([      "name":   "ÔÆº¬ÍÌÍÂ",
    "action" : "$N½£Ã¢ÍÌÍÂ£¬»ÃÈôÁéÉß£¬ÓÒÊÖ$wÊ¹³öÒ»Ê½"+(order[random(13)])+"¡¸ÔÆº¬ÍÌÍÂ¡¹"NOR"£¬½£ÊÆÂüÃî,´ÌÏò$nµÄ$l",
    "force" : 130,
    "dodge" : 25,
    "damage" : 300,
    "lvl" : 0,
    "damage_type" : "´ÌÉË"
]),
([      "name":   "ÃÎÐÑµû×¯",
    "action" : "$NÇüÍóÔÆ½££¬½£¹âÈç²Êµú·×·É£¬»Ã³öµãµãÐÇ¹â£¬ÓÒÊÖ$wÊ¹³öÒ»Ê½
"+(order[random(13)])+"¡¸ÃÎÐÑµû×¯¡¹"NOR"Ô¾Ô¾È÷È÷Æ®Ïò$nµÄ$l",
    "force" : 120,
    "dodge" : 125,
    "damage" : 320,
    "lvl" : 0,
    "damage_type" : "´ÌÉË"
]),
([      "name":   "ÈËÔÚåÚåÇ",
    "action" : "$N»Ó½£·Ö»÷£¬½£ÊÆ×ÔÐØÇ°Ô¾³ö£¬ÓÒÊÖ$wÒ»Ê½"+(order[random(13)])+"¡¸ÈËÔÚåÚåÇ¡¹"NOR"£¬ºÁÎÞ
ÁôÁµÖ®ÊÆ£¬´ÌÏò$nµÄ$l",
    "force" : 110,
    "dodge" : 115,
    "lvl" : 0,
    "damage" : 400,
    "damage_type" : "´ÌÉË"
]),
([      "name":   "ÇéÏµ¶Ì³¤",
    "action" : "$NÍË²½£¬×óÊÖ½£Ö¸»®×ª£¬Ñü²¿Ò»Å¤£¬ÓÒÊÖ$wÒ»¼Ç"+(order[random(13)])+"¡¸ÇéÏµ¶Ì³¤¡¹"NOR"×ÔÏÂ
¶øÉÏ´ÌÏò$nµÄ$l",
    "force" : 150,
    "dodge" : 135,
    "damage" : 400,
    "lvl" : 0,
    "damage_type" : "´ÌÉË"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry");}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 800)
                return notify_fail("ÄãµÄÄÚÁ¦²»¹»¡£\n");

        if ((int)me->query_skill("qinqi-shuhua", 1) < 100 && (int)me->query_skill("xuantian-wuji", 1)<150 )
                return notify_fail("ÄãµÄ±¾ÃÅÄÚ¹¦»ðºòÌ«Ç³¡£\n");
        return 1;
}
 mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("liangyi-jian",1);
        if (random(level) > 240 && me->query_skill("force") > 200 && me->query("neili") >= 500)
         {
        return ([
        "action":HIC"$NÉñÉ«ÄýÖØ£¬ÊÖÖÐ$w"NOR+HIY"Ò»¶Ù£¬ÆøËæÒâ×ª£¬$w"+HIY"ÉÏ½£Ã¢Í»Ê¢£¬
                   ÐÄÖÐÄ¬Äî½£¾÷£¬Èç±©·ç°ãµØ´ÌÏò$nµÄ$l£¡"NOR,
        "force" : 500,
        "dodge" : 140,
        "parry" : 140,
        "damage": 900,
        "weapon": HIY"½£î¸"NOR,
        "damage_type":  "´ÌÉË"
]);
}
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
    object weapon;

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
   return notify_fail("ÄãÊ¹ÓÃµÄÎäÆ÷²»¶Ô¡£\n");
    if ((int)me->query("qi") < 50)
   return notify_fail("ÄãµÄÌåÁ¦²»¹»Á·Á½ÒÇ½£·¨¡£\n");
    me->receive_damage("qi", 40);
    return 1;
}
string perform_action_file(string action)
{
    return __DIR__"liangyi-jian/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
       string msg;
       int j, k;
       j = me->query_skill("liangyi-jian", 1);
       k = me->query_skill("qinqi-shuhua",1);
       if( random(10) >= 5 
        && !me->is_busy() 
        && !victim->is_busy() 
        && j > 120
        && k > 120
        && me->query_skill_mapped("parry") == "liangyi-jian"
        && j > random(victim->query_skill("dodge",1))){
          switch(random(3)){
            case 0 :
               msg = HIW"$NÊ©Õ¹¿ª½£Â·£¬½£ÊÆºÆµ´Æð·ü£¬Ï¬ÀûÎÞ±È£¡\n"NOR;
               msg+= HIW"$nÁ¬Á¬ááÍË£¬È«Á¦ÕÐ¼Ü£¬ÎÞÁ¦»¹ÕÐ£¡\n"NOR;
               victim->start_busy(3);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 2);
               break;
            case 1 :
               msg = HIW"$NÈÆ×Å$n·É¿ìµØÐý×ª£¬Ò»ÏÂ×ÓÁ¬´Ì³öºÃ¼¸Ê®½££¡\n"NOR;
               msg+= HIW"$n¸ù±¾·Ö²»Çå³þÄÇÒ»½£ÊÇÐé£¬ÄÇÒ»½£ÊÇÊµ£¬ù£ºÃÍ£ÏÂ¹¥ÊÆ£¬ÑÏÊØÃÅ»§¡£\n"NOR;
               victim->start_busy(2);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 0);
               break;
            case 2 :
               msg = HIW"$N·ç³Ûµç³¸µÄÈÆÖø$n¿ìÅÜ£¬ºö¶«ºöÎ÷£¬¼òÖ±ÏñÊÇ×ã²»µãµØµÄ·ÉÐÐÒ»°ã£¡\n"NOR;
               msg+= HIW"$nËæ×Å$N×ªÀ´×ªÈ¥£¬ù£ÅªµÃÑÛ»¨çÔÂÒ£¬Ò¡Ò¡Óû×¹¡£\n"NOR;
               victim->start_busy(3);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1);
               break;
          }         
       }
}

