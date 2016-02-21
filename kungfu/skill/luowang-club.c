// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// luowang-club.c ½ôÄÇÂÞÍõ¹÷

#include <ansi.h> 
#include <combat.h>

inherit SKILL; 

mapping *action = ({ 
([      "action" :
       "$NÊÖÖÐµÄ¹÷ÉÒÓÉÏÂÍùÉÏÒ»ÁÃ,½ô½Ó×ÅÒ»ÕÐ[Ë³·ç´òÆì],ÄÇ¹÷Î²Ö± Íù$nµÄ$l´òÈ¥",     
       "force"  : 350, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 230, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" :"$Nµ¥ÍÈµãµØ£¬ÏòÉÏ°Î³öÕÉÓà£¬$w·ÉÎè»Ã³öÎÞÊý»ÃÓ°½«
$nÕÖ×¡£¬¿ÚÖÐ´óºÈÒ»Éù[Ñ©»¨¸Ç¶¥]£¬Ö»Ìý¹÷´ø·çÉùÎØÎØ×÷ÏìÏò$nµÄ$1ÅüÈ¥",     
       "force"  : 380, 
       "attack" : 200, 
       "dodge"  : -5, 
       "parry"  : -80, 
       "damage" : 250, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$N°Ñ$wÒ»¼Ü£¬µ²×¡ÁË$nµÄÈ¥Â·£¬$NÊÖÖÐµÄ$wÒ»Õñ£¬´øÆðÁËÍòÕÉ½ð¹â£¬
¡¡¡¡¡¡´ÓÕâÆ¬¹âÃ¢ÖÐ³å³öÒ»µÀÇåÑÌ£¬Ö±Ïò$nµÄ$1±¼È¥£¬ÕýÊÇÒ»ÕÐ£Û²¦ÔÆ¼ûÈÕ£Ý",
       "force"  : 400, 
       "attack" : 200, 
       "dodge"  : -40, 
       "parry"  : -105, 
       "damage" : 280, 
       "damage_type": "´ÌÉË" 
]), 
([      "action" :       "$NÊÖÖÐµÄ$wÒ»Õñ£¬ÒÔ¹÷ÐÐµ¶Ê½£¬´ó¿ª´óãØ,       
       $w»¯×öÁùµÀºÚÓ°Ïò$nµÄ$1¼¯ÖÐÅüÈ¥",      
       "force"  : 420, 
       "attack" : 180, 
       "dodge"  : -15, 
       "parry"  : -80, 
       "damage" : 280, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$NÉíÌåÏòºóÒ»×ª,´óºÈ:[ÎÚÁú°ÚÎ²],$w»¯×öÊýµÀ»ÃÓ°É¨Ïò$nµÄÑü²¿", 
       "force"  : 420, 
       "attack" : 190, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 290, 
       "damage_type": "ÕðÉË"
]), 
([     "action" : "$NÉíÐÐÒ»Õ¹,»¯Îª[Ñà×Ó´©ÁÖ]Ê½,ÊÖÖÐµÄ$w¿ìÈçÉÁµçµØ´ÌÏò$nµÄµÄ$l",
       "force"  : 450,
       "attack" : 150,
       "dodge"  : -20,
       "parry"  : -120,
       "damage" : 310,
       "damage_type": "´ÌÉË"
]), 
([     "action" : "$NÉíÌåÍùºóÒ»¶Ù,»»ÒÔÎÕÇ¹µÄÊÖ·¨,Ò»Ê½[òÔÁú³öË®],ÊÖÖÐµÄ$wÍù$nµÄ$l´ÌÈ¥",
       "force"  : 520, 
       "force" : 460, 
       "attack" : 160, 
       "dodge"  : -40, 
       "parry"  : -100, 
       "damage" : 90, 
       "damage_type": "´ÌÉË" 
]), 
([      "action" : "$NÊÖÖÐµÄ$wÎèÁË¸ö¹÷»¨£¬µ¥ÍÈ¶ÀÁ¢£¬$wÏòºóÒ»´ø£¬¿ÚÖÐ´óºÈÒ»Éù
¡¡¡¡¡¡¡¡[¶ÀÅü»ªÉ½]£¬Ö»Ìý$w´øÒ»ÉùºôÐ¥Ïò$nµÄ$1ÅüÈ¥",
       "force"  : 490, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -75, 
       "damage" : 320, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$NÑüÒ»°Ú£¬Ë«ÍÈË³ÊÆÅÌÍÈ×øÏÂ£¬ÊÖÖÐ$wÒ»¶¶£¬Ò»Ê½£ÛÏ¬Å£ÍûÔÂ],
       ÊÖÖÐµÄ$wÊÆÈç³¤ºç£¬ÓÉÏÂÍù$nµÄ$1´ÌÈ¥",    
       "force"  : 500, 
       "attack" : 150, 
       "dodge"  : -30, 
       "parry"  : -110, 
       "damage" : 340, 
       "damage_type": "´ÌÉË" 
]), 
([      "action" : "$NÊÖÖÐµÄ$w×óÓÒÀ¹É¨£¬Ò»°Ñ°Ñ$nÈ¦×¡,½ô½Ó×Å£¬$NÓÃ$w°Ñ$nÒ»Ìô£       
        ³¤Ð¥Ò»Éù:[ÂÞºº²«»¢],¹÷ÉÒ¾¶Ö±Ïò$nµÄ$1ÅüÈ¥",           
       "dodge"  : -25, 
       "force"  : 500, 
       "attack" : 170, 
       "dodge"  : -70, 
       "parry"  : -55, 
       "damage" : 350, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$NÊ¹³öÒ»ÕÐ[ÌìÂíÐÐ¿Õ],ÊÖÖÐµÄ$wÇáÓ¯×ÔÈçµØ»ÓÈ÷£¬Ïò$nµÄ$1µã»÷¹ýÈ¥",
       "force" : 510, 
       "attack" : 185, 
       "dodge"  : -30, 
       "parry"  : -100, 
       "damage" : 410, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" :        "$NÒ»Éù³¤Ò÷£¬$wÏòÍâÒ»²¦ÉíÌåË³ÊÆ¼±×ª£¬Í»È»¼±Í£Ïò
        $nµÄÉíÇ°Ô¾È¥£¬¿ÚÖÐ³¤Ð¥¡¸·ï»ËÕ¹³á¡¹¹÷ÉÒºáÉ¨$nµÄ$l",    
       "force"  : 510, 
       "attack" : 180, 
       "dodge"  : -50, 
       "parry"  : -110, 
       "damage" : 410, 
       "damage_type": "ÓÙÉË" 
]), 
([       "action" : "$NË«Ä¿¾«¹â±©³¤£¬ÉñÇéÅ­²»¿É¶ô£¬Ò»Ê½[ºáÉ¨Ç§¾ü]´ø¶¯
       ÎÞÊýµÀºÚÓ°,$wÖ±»÷$nµÄ$l²»´ý$n×ö³ö·´Ó¦£¬$w¾¹È»ºÁÎÞÕÂ·¨ËÆµÄÏò$nÈ«Éí
       ÂÒÅü¹ýÈ¥,ËÙ¶È¼«¿ì$nÖ»¾õÑÛÇ°¾¡ÊÇ¹÷Ó°¶ø²»¼ûÈË",     
       "force"  : 560, 
       "attack" : 170, 
       "dodge"  : -65, 
       "parry"  : -120, 
       "damage" : 500, 
       "damage_type": "ÓÙÉË" 
]), 
}); 

string main_skill() { return "luowang-club"; } 

mapping sub_skills = ([ 
       "shunfeng-daqi"         : 120,        // 1 
       "xuehua-gaiding"        : 120,        // 2 
       "boyun-jianri"          : 120,        // 3
       "liuding-kaishan"       : 120,        // 4
       "wulong-baiwei"         : 120,        // 5
       "yanzi-chuanlin"        : 120,        // 6
       "jiaolong-chushui"      : 120,        // 7
       "dupi-huashan"          : 120,        // 8
       "xiniu-wangyue"         : 120,        // 9
       "luohan-bohu"           : 120,        // 10
       "tianma-xingkong"       : 120,        // 11
       "fenghuang-zhanchi"     : 120,        // 12
       "hengsao-qianjun"       : 120,        // 13
]); 

int get_ready(object me) 
{ 
       return 1; 
} 

int get_finish(object me) 
{ 
       if (me->query("str") < 25 || me->query_str() < 45) 
       { 
               tell_object(me, "ÄãÑÝÁ·Íê±Ï£¬Õû¸öÉíÌå¼¸ºõÍêÈ«ÐéÍÑÁË£¬ÈíÃàÃàµÄÌá²»ÆðÒ»µã¾¢¡£\n"); 
               return 0; 
       } 

       if (me->query("con") < 25 || me->query_con() < 45) 
       { 
               tell_object(me, "ÄãÑÝÁ·Íê±Ï£¬¾Í¾õµÃÑÛÇ°½ðÐÇÂÒÃ°£¬Ì«ÑôÑ¨Í»Í»µÄÌø¡£\n"); 
               return 0; 
       } 

       if ((int)me->query_skill("force") < 200) 
       { 
               tell_object(me, "ÄãÑÝÁ·Íê±Ï£¬¼¸ºõÐéÍÑ£¬×Ô¼ºµÄÄÚ¹¦Ë®Æ½¿´À´»¹ÓÐ´ýÌá¸ß¡£\n"); 
               return 0; 
       } 

       if ((int)me->query("max_neili") < 1500) 
       { 
               tell_object(me, "ÄãÑÝÁ·Íê±Ï£¬µ¤ÌïÌá²»Æð°ëµãÁ¦À´£¬¿´À´Ó¦¸Ã¼ÌÐø¶ÍÁ¶ÄÚÁ¦¡£\n"); 
               return 0; 
       } 

       if (random(10) < 5) 
       { 
               tell_object(me, "Äã¶Ô½ôÄÇÂÞÍõ¹÷µÄ°ÂÃîÆÄÓÐÁìÎò£¬»òÐíÔÙÑÝÁ·Ò»´Î¾ÍÄÜ¹»ÈÚ»á¹áÍ¨¡£\n"); 
               return 0; 
       } 

       tell_object(me, HIY "ÄãÒ»ÆøºÇ³É£¬½«½ôÄÇÂÞÍõ¹÷´ÓÍ·µ½Î²ÑÝÁ·ÁËÒ»±ä£¬ÐÄÖÐ¶ÙÎò£¬Í¨\n" 
                           "ÏþÁËµÄ½ôÄÇÂÞÍõ¹÷°ÂÃî¾«Ëè£¬ÈÚ»á¹áÍ¨ÁË¹÷·¨µÄ¾«Î¢Ö®´¦£¬\n" 
                           "ÔÙÒ²²»ÊÇ²ð¿ªÊ¹ÓÃÄÇÃ´ÄÇÃ´¼òµ¥¡£\n" NOR); 
       return 1; 
} 

mapping query_sub_skills() 
{ 
       return sub_skills; 
} 

int valid_enable(string usage) { return usage=="club" ||  usage=="parry"; }   

int valid_learn(object me) 
{  
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "club")
                return notify_fail("ÄãÊÖÖÐÎÞ¹÷ÔõÃ´Ñ§Ï°°¡¡£\n");
       if ((int)me->query("str") < 25 &&
           (int)me->query("con") < 25) 
               return notify_fail("¾ÍÄãÕâÉí×Ó¹Ç»¹Á·½ôÄÇÂÞÍõ¹÷£¿Ð¡ÐÄÉíÌå³Ô²»Ïû°¡¡£\n"); 
       if ((int)me->query("int") < 20) 
               return notify_fail("ËãÁË°É£¬ÄãÏÈÌìÎòÐÔ²»ºÃ£¬ÔõÃ´ÄÜÀí½âÄØ¡£\n"); 
       if ((int)me->query_skill("force") < 200) 
               return notify_fail("ÄãµÄÄÚ¹¦»ðºò²»¹»£¬ÎÞ·¨Ñ§Ï°½ôÄÇÂÞÍõ¹÷¡£\n"); 
       if ((int)me->query_skill("hunyuan-yiqi") < 200) 
               return notify_fail("ÄãµÄ»ìÔªÒ»Æø¹¦»ðºò²»¹»£¬ÎÞ·¨Ñ§Ï°½ôÄÇÂÞÍõ¹÷¡£\n");
       if((int)me->query_skill("zui-gun") < 200) 
               return notify_fail("ÄãµÄ×í¹÷»ðºò²»¹»£¬ÎÞ·¨Ñ§Ï°½ôÄÇÂÞÍõ¹÷¡£\n"); 
       if ((int)me->query_skill("buddhism") < 200) 
               return notify_fail("ÄãµÄìø×ÚÐÄ·¨»ðºò²»¹»£¬ÎÞ·¨Ñ§Ï°ÓÚìø×ÚÏ¢Ï¢Ïà¹Ø½ôÄÇÂÞÍõ¹÷¡£\n"); 
       if ((int)me->query("max_neili") < 2000) 
               return notify_fail("ÄãµÄÄÚÁ¦ÕâÃ´²î£¬ÔõÄÜÈÚ»á¹áÍ¨½ôÄÇÂÞÍõ¹÷£¿\n"); 

       if ((int)me->query_skill("club", 1) < 200) 
               return notify_fail("ÄãµÄ»ù±¾¹÷·¨»ðºò²»¹»£¬ÎÞ·¨Ñ§Ï°½ôÄÇÂÞÍõ¹÷¡£\n"); 
       if ((int)me->query_skill("club", 1) < (int)me->query_skill("luowang-club", 1)) 
       return
   notify_fail("ÄãµÄ»ù±¾¹÷·¨Ë®Æ½ÓÐÏÞ£¬ÎÞ·¨Áì»á¸ü¸ßÉîµÄ½ôÄÇÂÞÍõ¹÷¡£\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
       mapping a_action;
       int level;

       level = (int)me->query_skill("luowang-club", 1);
       a_action = action[random(sizeof(action))]; 
       a_action["dodge"] -= level / 10;
       a_action["parry"] -= level / 10;
       a_action["attack"] += level / 10;
       a_action["force"] += level / 10;
       a_action["damage"] += level / 10;
       if (me->query_temp("action_flag"))
                me->set_temp("action_msg","½ô¸ú×Å");
       return a_action;
} 

int practice_skill(object me) 
{ 
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "club")
                return notify_fail("ÄãÊÖÖÐÎÞ¹÷ÔõÃ´Á·°¡¡£\n");
     if ((int)me->query("qi") < 150) 
               return notify_fail("ÄãµÄÌåÁ¦Ì«µÍÁË¡£\n"); 
       if ((int)me->query("neili") < 100) 
               return notify_fail("ÄãµÄÄÚÁ¦²»¹»Á·½ôÄÇÂÞÍõ¹÷¡£\n"); 

       me->receive_damage("qi", 120); 
       me->add("neili", -50); 
       return 1; 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        if (random(10) >= 1)
       { 
               victim->receive_wound("qi", damage_bonus); 
               victim->receive_wound("jing", damage_bonus); 
               return HIR "Ëæ×ÅÒ»Éù³ÁÃÆµÄºßÉù´«À´£¬$nµÄ¿ÚÖÐ¿È³öÁË¼¸¿ÚÏÊÑª£¡\n" NOR; 
       } 
} 

string perform_action_file(string action) 
{ 
       return __DIR__"luowang-club/" + action; 
} 

void skill_improved(object me) 
{ 
       int i; 
       string *sub_skillnames; 

       sub_skillnames = keys(sub_skills); 
       for (i = 0; i < sizeof(sub_skillnames); i++) 
               me->delete_skill(sub_skillnames); 
} 
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;
    
        skill = me->query_skill("luowang-club", 1);
        if (skill > 120 && ! objectp(weapon = me->query_temp("weapon")))
        {
                enemy=me->query_enemy();
                if (! sizeof(enemy)) return;
                for (i=0;i<sizeof(enemy);i++)
                {
                        for (j=0;j<(skill/(60*sizeof(enemy)));j++)
                        if ((me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && enemy[i]->query("qi")>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        me->add_temp("str",skill/10);
                                        me->add_temp("dex",skill/10);
                                        COMBAT_D->do_attack(me, enemy[i], me->query_temp("weapon"), TYPE_REGULAR);
                                }
                        } else break;
                }
                me->delete_temp("str");
                me->delete_temp("dex");
        }
}


