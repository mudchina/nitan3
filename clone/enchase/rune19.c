//rune19.c

// Fal 法爾

#include <ansi.h>

inherit ITEM;

int is_rune_ob() { return 1; }
int is_enchase_ob() { return 1; } 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune fal", "rune19", "rune"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：法爾(FAL)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 19);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100); 
                set("enchase/wspe_data", ([
                        "add_magic"      : 30,               
                ]));
                set("enchase/aspe_data", ([
                        "avoid_magic"    : 10,     
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

