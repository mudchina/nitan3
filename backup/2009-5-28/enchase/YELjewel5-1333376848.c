// SN:On7C=EIC^\S6hGL4
//  Written by ZHANG TIANSHI(Lonely 2007/10/15)	Wed May 27 10:18:32 2009
#include <ansi.h>
inherit ITEM;

int is_enchase_ob(){ return 1; }

void create()
{
	set_name(YEL "圣之宝石" NOR, ({ "YEL jewel5" }));
	set_weight(50);
	set("unit", "块");
	set("long", YEL "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR );
	set("value", 160000);
	set("enchase/SN", 9);
	set("enchase/level", 5);
	set("enchase/cur_firm", 83);
	set("enchase/wspe_data", ([
		"learn_times" : 5,
		"add_lighting" : 17,
		"str" : 6,
		"max_jing" : 600,
		"da_power" : 5,
	]));
	set("enchase/aspe_data", ([
		"reduce_poison" : 17,
		"learn_times" : 5,
		"research_times" : 5,
		"avoid_cold" : 5,
		"learn_times" : 5,
	]));
	set("wear_msg", HIC "$N" HIC "轻轻地把$n"HIC "戴在头上。\n" NOR);
	set("remove_msg", HIC "$N" HIC "轻轻地把$n"HIC "从头上摘了下来。\n" NOR);

	setup();
}

int query_autoload(){ return 1; }
