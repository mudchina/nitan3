#include "herb.h"

void create()
{
        set_name(HIB "���" NOR, ({ "gui jia", "gui", "jia", "herb_guijia" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "�ڹ�Ŀǣ������и��ֻ��ƣ�������ҩ��\n" NOR);
                set("base_unit", "��");
                set("base_value", 5000);
                set("base_weight", 80);
        }
        setup();
}