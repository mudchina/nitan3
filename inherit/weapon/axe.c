// axe.c

#include <weapon.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

varargs void init_axe(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
	set("flag", (int)flag | EDGED);
	set("skill_type", "axe");
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "chop", "slice", "hack" }) );
	}
}

string extra_long()
{
        string str;
        
        str =  "物品类型    ：    兵器\n";
        str += "属    性    ：    斧\n";
        str += sprintf("攻    击    ：    %d\n", query("weapon_prop/damage"));
       str += sprintf("重    量    ：    %d\n", this_object()->query_weight());
        str += sprintf("杀    戮    ：    %d\n", query("combat/PKS"));
        str += sprintf("使用方式    ：    输入指令 wield %s 装备。\n", query("id"));
        str += sprintf("                  输入指令 unwield %s 卸下。\n", query("id"));
        if (this_object()->query_autoload())
                str += "下线丢失    ：    否\n";
        else
                str += "下线丢失    ：    是\n";
        return str;
}
