// SN:\3g476<hX85N>6lh
//  Written by ZHANG TIANSHI(Lonely 2007/10/15)	Wed May 27 10:19:58 2009
#include <ansi.h>
inherit ITEM;

int is_enchase_ob(){ return 1; }

void create()
{
	set_name(WHT "宝石" NOR, ({ "WHT jewel2" }));
	set_weight(50);
	set("unit", "块");
	set("long", WHT "一块金光闪闪的精美宝石，华丽异常。\n" NOR );
	set("value", 100000);
	set("enchase/SN", 5);
	set("enchase/level", 2);
	set("enchase/cur_firm", 83);
	set("enchase/wspe_data", ([
		"add_fire" : 8,
		"max_qi" : 300,
	]));
	set("enchase/aspe_data", ([
		"avoid_cold" : 2,
		"max_qi" : 300,
	]));
	set("wear_msg", HIC "$N" HIC "轻轻地把$n"HIC "戴在头上。\n" NOR);
	set("remove_msg", HIC "$N" HIC "轻轻地把$n"HIC "从头上摘了下来。\n" NOR);

	setup();
}

int query_autoload(){ return 1; }
