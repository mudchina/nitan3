#include <ansi.h>
inherit ROOM;
string look_notice();

void create()
{
        set("short", "��ɽ����");
        set("long", HIW @LONG
                          
                         ���ִ��㳡
                          
                          
    ���ϴ˴���ֻ����ǰ��һ��Բ��ʮ�ɵ�ƽ̨��������һ͹��Լ�ɸߵ�ʯ̨��
��ʯ�Ͽ������绪ɽ�۽������а�(notice)����ƺ�Ķ�������һ�����ߵ���̴
ľ�ܣ�����һ��Ѫ��ɫ�Ĵ�ģ����俪ʼ��̨�ϻ�ݳ�һ������(paizi)��
����չʾ��ǰ��������̣��嶥��������Ʈ�죬�·������󺣣���ɽ���纣��
С�������������壬����һ��ʢ����������
LONG NOR
    );
        set("item_desc", ([ /* sizeof() == 1 */
                "���" : "����һֻţƤ�Ƴɵľ޹ģ�������ʿ�ڻ�ɽ�۽�ʱ����(knock)����ʼ���䡣",
                "notice" : (: look_notice :),
        ]));
        set("exits", ([ /* sizeof() == 2 */
                "southdown" : "/d/huashan/houzhiwangyu",
        ]));
        
        set("outdoors", "huashan" );

        set("no_fight", 1);
        set("no_quit", 1);
        set("objects", ([
                // "/clone/misc/drum2" : 1,
        ]));
        setup();
}
void init()
{
        object me = this_player();
        add_action("get_weapon", ({ "na", "qu", })); 
        add_action("discmds", ({
                "respitate", "exert", "array", "ansuan", "touxi", "persuade", 
                "teach", "exert", "exercise", "study", "learn", "sleep", "kill",
                "steal", "cast", "conjure", "expell", "fight", "hit", "perform", 
                "prcatice", "scribe", "surrender", "sha", "recall", "quit", "exit"}));
        call_out("do_recover", 1, me);
}
void do_recover(object me)
{
        if (! me || environment(me) != this_object()) return;
                me->delete("no_get");
        if (! living(me)) me->revive();
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("max_jing"));
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("max_qi"));
        if (me->query("neili") < me->query("max_neili"))
                me->set("neili", me->query("max_neili"));
        if (me->query("jingli") < me->query("max_jingli"))
                me->set("jingli", me->query("max_jingli"));
        me->clear_condition();
        me->set("food", me->max_food_capacity());
        me->set("water", me->max_water_capacity());
        me->start_busy(0);
}
int discmds()
{
        tell_object(this_player(), "�����㻹��ר�Ŀ�����ɣ�\n");

        return 1;
}
int get_weapon(string arg)
{
        object me, ob;
        
        me = this_player();
        
        if (! arg) return notify_fail("��Ҫ��ȡʲô��Ʒ��\n");
        
        switch (arg) 
        {
        case "cloth":
                ob = new("/clone/cloth/cloth");
                break;
        case "sword":
                ob = new("/clone/weapon/changjian");
                break;
        case "blade":
                ob = new("/clone/weapon/blade");
                break;
        case "staff":
                ob = new("/clone/weapon/zhubang");
                break;
        case "whip":
                ob = new("/clone/weapon/changbian");
                break;
        case "hammer":
                ob = new("/clone/weapon/hammer");
                break;
        default:  
                return notify_fail("��Ҫ��ȡʲô��Ʒ��\n"); 
                break;
        }
        
        ob->move(me);
        
        tell_object(me, "��Ӽ�������������Ҫ����Ʒ��\n");
        return 1;
}
        
string look_notice()
{
        object who;
        string *name_list, file;
        int i, j = 0, k;
        
        who = this_player();
        file = read_file("/log/static/lunjian");
        if (! file)
                return "Ŀǰû���κα����¼��\n";
        name_list = explode(file,"\n");
        for (i = 0; i < sizeof(name_list); i++) 
        {
                if (name_list[i] == "seperator") 
                {
                        j++;
                        k = 0;
                        printf("\n��" + chinese_number(j) + "�컪ɽ�۽������\n");
                        continue;
                }
                k++;
                printf(GRN "��" + chinese_number(k) + "����%-50s\n" NOR, name_list[i]);
        }
        return "\n";
}
