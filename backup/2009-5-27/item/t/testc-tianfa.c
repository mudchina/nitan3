// SN:IQ=0;48RoX=Z`HHQ
// ITEM Made by player(ÕÅ¶şĞ¡:testc) /data/item/t/testc-tianfa.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat May 23 11:05:51 2009
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÌì·£[2;37;0m", ({ "tianfa" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÎŞÃûÖ®Îï[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÕÅ¶şĞ¡(testc)
");
	set("value", 1);
	set("point", 526);
	set("material", "noname object");
	set("material_file", "/clone/item/noname");
	set("wield_msg", "[1;36m$N[1;36mÒ»ÉùÇåĞ¥£¬¶¶³öÒ»±ú[1;36m$n[1;36m¡£[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
