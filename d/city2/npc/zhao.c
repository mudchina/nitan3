inherit NPC;
#include <ansi.h>

string clear_degree(string arg);
int add_degree(object ob);

void create()
{
        set_name(HIY"赵一仁"NOR, ({"zhao yiren", "zhao", "yiren"}));
        set("nickname", HIR"兵部尚书"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long", 
         "他就是当今兵部大大有名的尚书赵一仁，在朝中极有权势。\n"
        );

        set("attitude", "friendly");
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);

        set("chat_chance", 5);

        set("chat_msg", ({
        "赵一仁叹了口气道：最近怎么没什么人来送礼了，看来得想想办法了。\n",
        }));

        set("inquiry", ([
        "功名" : "要求取功名，好啊，可是老夫近来身体不适，这个。。。", 
        ]));

        setup();
        carry_object("clone/misc/cloth")->wear();
}

/*
int add_degree(object ob)
{
        string degree,old_degree;

        degree=HIC "裨将" NOR;
        if( ob->query("degree") ) old_degree=ob->query("degree");
        else old_degree="";

        message("channel:rumor",MAG"【大宋京城】"HIY"奉天承命，皇帝诏曰："
        +"策封 "+old_degree+" "+HIW+ob->query("name")
        +HIY" 为大宋 "NOR+degree+HIY"，钦此！\n"NOR,users());
        ob->delete_temp("degree_jungong");

        if( ob->query("degree") )
        {
         if( ob->query("degree_ask") )
         degree=HIM " ☆ " NOR+clear_degree(ob->query("degree"))
              +HIM " ☆ " NOR+degree+HIM " ☆ "NOR;
          else
         degree=HIM " ☆ " NOR+clear_degree(ob->query("degree"))
              +degree+HIM " ☆ " NOR;
        } else
         degree=HIM " ☆ " NOR+degree
              +HIM " ☆ " NOR;               

        ob->set("degree_jungong",4);
        ob->set("degree",degree);
        return 1;
}

string clear_degree(string arg)
{
        if( (strsrch(arg, BLU "士卒" NOR) >= 0) ||
            (strsrch(arg, BLU "游击" NOR) >= 0) ||
            (strsrch(arg, HIC "参将" NOR) >= 0) ||
            (strsrch(arg, HIC "裨将" NOR) >= 0) ||
            (strsrch(arg, HIM " ☆ " NOR) >= 0))
         {
            arg = replace_string(arg, BLU "士卒" NOR,"");
            arg = replace_string(arg, BLU "游击" NOR,""); 
            arg = replace_string(arg, HIC "参将" NOR,"");
            arg = replace_string(arg, HIC "裨将" NOR,"");   
            arg = replace_string(arg, HIM " ☆ " NOR,"");
          }
          return arg;
}

int accept_object(object who, object ob)
{
        if ( who->query("degree_jungong") >= 4)
        {
         message_vision("$N一脸愤慨：你我同朝为官，如何使这种不仁不义"
                        +"之举？来呀，把"+who->query("name")
                        +"给我轰出去！！\n"+"$n被一群家将连推带打地轰"
                        +"出了尚书府！！\n"NOR,this_object(),who);
         who->move("/d/city2/ydmen");
         return 0;
        }

        if ( ob->query("money_id") && ob->value() >= 10000000 )
        {
          message_vision(HIW"$N一张脸顿时笑颜大开：请稍侯，老夫为你进宫"
          +"走走。\n", this_object());
          this_object()->move("/d/city2/cddian");
          call_out("add_degree",10,who);
          return 1;
        } else
        {
          message_vision(HIY"$N大怒：给我滚出去！$n被一群家将连推带打地"
           +"轰出了尚书府！！\n"NOR, this_object(),who);
          who->move("/d/city2/ydmen");
          return 0;
        }
}
*/
