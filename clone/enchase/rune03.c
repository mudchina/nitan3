//rune03.c

// Tir 特爾

#include <ansi.h>

inherit ITEM;

int is_rune_ob() { return 1; }
int is_enchase_ob() { return 1; } 
void create()
{
        set_name(HIW "符文" NOR, ({ "rune tir", "rune03", "rune"}));
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "符文：特爾(TIR)，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 3);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100); 
                set("enchase/wspe_data", ([
                        "max_experience": 600000,                 
                ]));
                set("enchase/aspe_data", ([
                        "max_experience": 500000,       
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }

