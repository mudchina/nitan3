// xunying.c 遁影擒踪

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "遁影擒踪" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你在解体过程中纵观天象，察觉到了人世\n"
                           "间的诸多奥秘，众生百态尽收眼底。此后\n"
                           "不再受到架力卸招之技的迷惑。\n");
}
