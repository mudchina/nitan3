// ÕâÊÇÍæ¼Ò×Ô´´Îä¹¦³ÌÐò Ô­ÓÉmaxim@nju_fengxue±àÐ´£¬ÏÖÓÉxgchen@zzfyÐÞ¸Ä
// sunset
// ÈÕ²»Âä
// [1;36måÐÒ£»¤·¨[2;37;0m
// 6197214
// ÄÐÐÔ
// blade
// É±ÈËµ¶·¨





inherit SKILL;

////////////////////////////////

mapping *action = ({

// ZHAOSHI :0

([
"action" :"$NºöµØÆËÉÏÈ¥£¬Ò»ÕÐ¡¸Òª$NµÄÃü¡¹£¬ÊÖÖÐ$w´óÆð´óÂä£¬ºÁÎÞ°ëµã¹æ¾Ø¿ÉÑ­£¬ºÝºÝ¿³Ïò$nµÄ$l",
"force" :50,
"dodge" :20,
"damage_type": "¸îÉË",
"attack" : 50,
"parry" : 50,
"lvl" : 0,
"skill_name" : "ÒªÄãµÄÃü"
]),
 });
// ZHAOSHI :1
int valid_learn(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon"))
     || (string)weapon->query("skill_type") != "blade") return notify_fail("ÄãÊ¹ÓÃµÄÎäÆ÷²»¶Ô¡£\n");
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("ÄãµÄÄÚÁ¦Ì«Èõ£¬ÎÞ·¨Á·"+"É±ÈËµ¶·¨"+"¡£\n");
        return 1;
}
int valid_enable(string usage) { return usage=="blade" || usage=="parry"; }
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int i, level;
    level = (int)me->query_skill("sunset-blade",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade") return notify_fail("ÄãÊ¹ÓÃµÄÎäÆ÷²»¶Ô¡£\n");    if( (int)me->query("qi") < 100 )
                return notify_fail("ÄãµÄÌåÁ¦²»¹»ÁË£¬ÐÝÏ¢Ò»ÏÂÔÙÁ·°É¡£\n");
        if( (int)me->query("neili") < 100 )
                return notify_fail("ÄãµÄÄÚÁ¦²»¹»ÁË£¬ÐÝÏ¢Ò»ÏÂÔÙÁ·°É¡£\n");
        me->receive_damage("qi", 90);
        me->add("neili", -70);
        return 1;
} //total 34 lines!
string perform_action_file(string action)
{
        return __DIR__"meskill/" + action;
}
