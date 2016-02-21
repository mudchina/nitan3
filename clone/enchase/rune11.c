//rune11.c

// Amn 安姆

#include <ansi.h>

inherit ITEM;

int is_rune_ob() { return 1; }
int is_enchase_ob() { return 1; } 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune amn", "rune11", "rune"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：安姆(AMN)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 11);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100); 
                set("enchase/wspe_data", ([
                        "avoid_parry"   : 20,                 
                ]));
                set("enchase/aspe_data", ([
                        "max_qi"        : 1000,       
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

