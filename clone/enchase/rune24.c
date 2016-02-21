//rune24.c

// Ist 伊司特

#include <ansi.h>

inherit ITEM;

int is_rune_ob() { return 1; }
int is_enchase_ob() { return 1; } 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune ist", "rune24", "rune"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：伊司特(IST)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 24);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100); 
                set("enchase/wspe_data", ([
                        "max_jing"      : 4000,              
                ]));
                set("enchase/aspe_data", ([
                        "max_jing"      : 2000,   
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

