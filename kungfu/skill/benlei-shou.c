// benlei-shou.c ±¼À×ÊÖ
// By Alf
//À×¶¯·çÐÐ¡¡´ºÀ×Õ§ÏÖ¡¡À×±¼ÔÆÚÜ¡¡µçÉÁÀ×Ãù¡¡ÄÁÒ°¾ªÀ×¡¡À×¶¯¾ÅÌì¡¡À×¾ªµçÈÆ¡¡À×öªÍò¾û

inherit SKILL;

mapping *action = ({
([      "action" : "$N¿ÚÖÐµÍºÈ£¬×óÕÆµþÓÚÓÒÕÆÖ®ÉÏ£¬Ê©Õ¹³ö¡¸À×¶¯·çÐÐ¡¹£¬ÃÍÈ»ÅüÏò$n",
        "force" : 130,
        "dodge" : 20,
        "damage" : 10,
        "lvl" : 0,
        "skill_name" : "À×¶¯·çÐÐ",
        "damage_type" : "ÄÚÉË"
]),
([      "action" : "$NÍÂÆøÑïÉù£¬Ò»ÕÐ¡¸´ºÀ×Õ§ÏÖ¡¹£¬Ë«ÕÆÇáÆ®Æ®µØÅÄÏò$nµÄ$l",
        "force" : 150,
        "dodge" : 10,
        "damage" : 30,
        "lvl" : 20,
        "skill_name" : "´ºÀ×Õ§ÏÖ",
        "damage_type" : "ÄÚÉË"
]),
([      "action" : "$N´óÐ¦²»¾ø£¬Ë«ÕÆ·­·É£¬»Ã»¯ÈçÔÆ£¬Ò»ÕÐ¡¸À×±¼ÔÆÚÜ¡¹ÒÑ½«$nÁýÕÖÓÚÄÚ",
        "force" : 150,
        "dodge" : 30,
        "damage" : 35,
        "lvl" : 30,
        "skill_name" : "À×±¼ÔÆÚÜ",
        "damage_type" : "ÄÚÉË"
]),
([      "action" : "$NÒ»ÉùÇáß³£¬Ò»Ê½¡¸µçÉÁÀ×Ãù¡¹£¬Ë«ÕÆÒ»Ç°Ò»ºó£¬Ñ¸¼²¹¥Ïò$nµÄ$l",
        "force" : 250,
        "dodge" : 20,
        "damage" : 10,
        "lvl" : 40,
        "skill_name" : "µçÉÁÀ×Ãù",
        "damage_type" : "ÄÚÉË"
]),

([      "action" : "$NµÍºÈÒ»Éù£¬Ë«ÕÆÆ½»Ó£¬ÈçÀ×±¼ÐÐ°ã»÷Ïò$n£¬ÕýÊÇÒ»ÕÐ¡¸ÄÁÒ°¾ªÀ×¡¹",
        "force" : 300,
        "dodge" : 25,
        "damage" : 50,
        "lvl" : 60,
        "skill_name" : "ÄÁÒ°¾ªÀ×",
            "damage_type" : "ÄÚÉË"
]),
([      "action" : "$NÅ­ºÈÒ»Éù£¬ÉíÐÎ¶¸È»°ÎÆð£¬Ë«ÕÆÏÂ»÷£¬Ò»ÕÐ¡¸À×¶¯¾ÅÌì¡¹¹¥Ïò$nµÄ¶¥ÃÅ",
        "force" : 350,
        "dodge" : 30,
        "damage" : 80,
        "lvl" : 70,
        "skill_name" : "À×¶¯¾ÅÌì",
        "damage_type" : "ÄÚÉË"
]),
([      "action" : "$NÇáß³ÉùÖÐ£¬×óÕÆÐé»Î£¬ÓÒÕÆÒ»ÕÐ¡¸À×¾ªµçÈÆ¡¹£¬åÉ»÷$nµÄÐØ¸¹Ö®¼ä",
        "force" : 350,
        "dodge" : 30,
        "damage" : 90,
        "lvl" : 80,
        "skill_name" : "À×¾ªµçÈÆ",
           "damage_type" : "ÄÚÉË"
]),
([      "action" : "$NÒ»Éù³¤Ð¥£¬Ë«ÕÆÐ®·ç£¬ËÆ¼ýÀëÏÒ£¬Ê©³ö¡¸À×öªÍò¾û¡¹Í¬Ê±»÷Ïò$nµÄ$l",
        "force" : 450,
        "dodge" : -10,
        "damage" : 120,
        "lvl" : 100,
        "skill_name" : "À×öªÍò¾û",
    "damage_type" : "ÄÚÉË"
])
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("Á·±¼À×ÊÖ±ØÐë¿ÕÊÖ¡£\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("ÄãµÄÄÚÁ¦Ì«Èõ£¬ÎÞ·¨Á·±¼À×ÊÖ¡£\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("benlei-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("ÄãµÄÌåÁ¦Ì«µÍÁË¡£\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("ÄãµÄÄÚÁ¦²»¹»Á·±¼À×ÊÖ¡£\n");
        me->receive_damage("qi", 25);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"benlei-shou/" + action;
}

