// gangbiao.c
#include <weapon.h>
inherit THROWING;

void create()
{
        set_name("����", ({"gangbiao", "biao" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ����ͨ�ĸ��ڡ�\n");
                set("unit", "Щ");
                set("base_value", 1);
                set("material", "steel");
                set("base_unit", "ö");
                set("base_weight", 10);
        }
        set_amount(1);
        init_throwing(25);
        setup();
}
