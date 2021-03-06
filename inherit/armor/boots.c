// boots.c

#include <armor.h>

inherit EQUIP;

void setup()
{
	if (! clonep(this_object()))
	        set("armor_type", TYPE_BOOTS);

        ::setup();
}

int washed(int n)
{
        switch (query("material"))
        {
        case "cloth":
                n += n * 3 / 10;
                break;
        case "leather":
                break;
        case "silk":
                n -= n * 3 / 10;
                break;
        case "bamboo":
                n -= n * 5 / 10;
                break;
        case "steel":
                n -= n * 7 / 10;
                break;
        }
        set_temp("no_wear", "现在" + name() + "还是湿乎乎的，你没法穿。\n");
        delete_temp("daub");
        remove_call_out("dry_cloth");
        if (n) call_out("dry_cloth", n);
        return n;
}

void dry_cloth()
{
        if (! objectp(this_object()))
                return;
        delete_temp("no_wear");
        message("vision", name() + "已经干了。\n", environment());
}
string extra_long() 
{

        string str; 

        str =  "物品类型    ：    防具\n"; 
        str += "属    性    ：    靴子\n"; 
        str += sprintf("防    护    ：    %d\n", query("armor_prop/armor")); 
        str += sprintf("重    量    ：    %d\n", this_object()->query_weight());
        str += sprintf("使用方式    ：    输入指令 wear %s 装备。\n", query("id")); 
        str += sprintf("                  输入指令 remove %s 卸下。\n", query("id")); 
        if (this_object()->query_autoload()) 
               str += "下线丢失    ：    否\n"; 
        else 
               str += "下线丢失    ：    是\n"; 
        return str; 
}
