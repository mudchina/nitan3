inherit NPC;

void create()
{
        set_name("红娘", ({ "hong niang", "hongniang", "marriage witness" }));
        set("long", 
                "她是一个长得很好看的小姑娘，忽闪忽"
                "闪的大眼睛透着一丝狡黠。\n");
        set("gender", "女性");
        set("age", 18);
        set("combat_exp", 1000);

        setup();

}

