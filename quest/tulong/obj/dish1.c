#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIW"���˭������÷"NOR, ({"dish"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ����ţ������ÿ��ţ�ⶼ��������С����ƴ�ɣ�������ӡ�\n");
                set("unit", "��");
                set("value", 120);
                set("food_remaining", 16);
                set("food_supply", 30);
        }
}
