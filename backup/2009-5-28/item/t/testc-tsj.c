// SN:X\Udc9PJ=?FJK]4Z
// ITEM Made by player(ÕÅ¶şĞ¡:testc) /data/item/t/testc-tsj.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat May 23 11:08:48 2009
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÌìÉñ¼×[2;37;0m", ({ "tsj" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[1;35mÎŞÃûÖ®Îï[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÕÅ¶şĞ¡(testc)
");
	set("value", 1);
	set("point", 421);
	set("material", "noname object");
	set("material_file", "/clone/item/noname");
	set("wear_msg", "[33m$N[33m×°±¸[1;31mÌìÉñ¼×[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;31mÌìÉñ¼×[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
