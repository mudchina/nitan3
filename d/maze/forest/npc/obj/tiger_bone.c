#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("����", ({"tiger bone"}) );
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "���ǡ�\n" NOR);
                set("base_unit", "��");
                set("base_value", 8000);
                set("base_weight", 500);
        }
        setup();
        set_amount(1);
}
