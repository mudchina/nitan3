// Room: carol/heimuya

#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_insert(string arg);
int do_push(string arg);
void goto_heimuya(object ob);

void create()
{
    set("short", "日月坪");
        set("long", @LONG
这里是半山的一片小土坪，离崖顶还有一段路途，可到这已经没有路上去，
面前是如境般的峭壁，仰头而望，但见崖顶依稀耸立着楼阁，宛如仙境。可云烟
缭绕，看不清晰。从悬崖上垂下一条绳索(rope)，看上去象是悬崖上下互通消息
的工具，绳索的上面似乎隐约有一个吊篮(basket)。悬崖的墙上似乎有一个匣子
(xiazi) ，你似乎走入一个雾宅，真不知如何是好。
LONG );

    set("exits", ([
        "eastdown" : "/d/heimuya/shimen",
    ]));
    set("objects", ([
        CLASS_D("riyue") + "/zhang1" : 1,
    ]));

    set("outdoors", "heimuya");
    set("no_fight",1);
    set("item_desc", ([
        "basket": "那是一个掉篮，看样子有些古怪。\n",
        "rope"  : "绳子就是绳子，可能是向上的工具。\n",
        "xiazi" : "这是一个匣子，好像可以按(push)下去。匣子的侧面有一个插孔。\n",
    ]));

    setup();
}

void init()
{
    add_action("do_insert", "insert");
    add_action("do_push", "push");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object("/d/heimuya/basket")) )
            room = load_object("/d/heimuya/basket");
        if( room = find_object("/d/heimuya/basket") ) {
            if((int)room->query("insert_trigger")==0 ) {
                room->set("insert_trigger", 1);
                set("exits/enter", "/d/heimuya/basket");
                room->set("exits/out", __FILE__);
                message("vision", "“叭”的一声，你手中的令牌已被折断，只见一个"
                        "掉篮(basket)从天而降，你不禁一怔！\n", this_object());
                set("item_desc", ([
                    "basket" : "这是一个掉篮，是传说中的交通工具。\n",
                ]));
                
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "看样子你得等下拨儿。\n",this_object() );
        }
        else
            message("vision", "ERROR: basket not found\n", this_object() );
    }
}

void on_board()
{
    object room, me = this_player();
    if( !query("exits/enter") ) return;
    tell_object(me, HIG"只见掉篮缓缓向上，四周无限美好，"
                "你似乎置身于一处人间仙境无异。\n"NOR);

    if( room = find_object("/d/heimuya/basket") )
    {
        room->delete("exits/out");
    }
    delete("exits/enter");
    remove_call_out("arrive");
    call_out("arrive",20);
}

void arrive()
{
    object room;
    if( room = find_object("/d/heimuya/basket") )
    {
        room->set("exits/out", "/d/heimuya/up2");
        message("vision", "噔的一声，你似乎一下从天上到了地上。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object("/d/heimuya/basket") )
    {
        room->delete("exits/out");
        room->delete("insert_trigger");
    }
}

int do_insert(string arg)
{
    string dir;
    object ob;
    object me;

    me=this_player();

    if( !arg || arg=="" )   return 0;

    if( arg=="卡" )   arg = "card1";

    if( arg=="card1")
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");
        if( !me->query_temp("mark/cards") )
                me->set_temp("mark/cards",1);
        if( me->query_temp("mark/cards")==4)
        {
                me->delete_temp("mark/cards");
                destruct(ob);
                check_trigger();
        }
        else    {
                me->add_temp("mark/cards",1);
                message("vision", "噔的一声，你看到掉篮向下一节。\n",me );
        }
    }
    else
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");
        else    return notify_fail(ob->name() + "好像跟插孔不合，怎么也插不进去。\n");
    }
    return 1;
}

int do_push(string arg)
{
    object ob, myenv;
    ob = this_player();

    if( !arg || arg != "xiazi" )
         return notify_fail("你要 push 什么？\n");

    if (ob->query("family/family_name") == "日月神教")
    {
         message_vision("$N把匣子按了几下，只听“吱扭吱扭”几声，从崖上落下一个大吊篮。\n", ob);
         message_vision("$N一弯腰进了吊篮，吊篮缓缓地绞上崖去......\n", ob);
         myenv = environment(ob);
         ob->move ("/d/heimuya/basket");
         call_out("goto_heimuya", 10, ob);
         return 1;
    }
    else
         message_vision("$N把匣子按了几下，但好像没什么作用。\n",ob);
    return 1;
}

void goto_heimuya(object ob)
{
    tell_object(ob , "你眼前一亮，一幢幢白色建筑屹立眼前，霎是辉煌。\n");
    ob->move("/d/heimuya/chengdedian");
}

