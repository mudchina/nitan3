inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "ÈıÇåºş");
        set("long",
"[1;32mºşË®Çå³ºÍ¸Ã÷£¬²»Ê±¿ÉÒÔ¿´µ½¼¸Î²ÓãÌøÉÏË®Ãæ¡£ºşË®¾¡Í·ÊÇ\n"
"Ò»¸ö´óÆÙ²¼¡£ÔÚÕâÀï¿ÉÒÔÌıµ½ÆÙ²¼´ÓÉ½ÉÏÖ±³å¶øÏÂ£¬·¢³öµÄºäºäÀ×Éù¡£ºş\n"
"±ßÒ»¿é¾ŞÊ¯£¬ÉÏĞ´£¢ÈıÇåºş£¢¡£ÕâÀï·ç·Ç³£´ó£¬´µµÃÈËµÃÒÂÉÀÁÔÁÔ×öÏì¡£\n"
);
   set("exits", ([ 
      "northeast" : "/d/dragon/lake1",
   ]));

        set("no_magic", 1);
	setup();
}

void kite_notify(object obj, int i)
{
   object  me, room;
   int j;
        
   me = this_player();
   message_vision("Í»È»Ò»ÕóÎ¢·ç·÷¹ı"+obj->name()+"»º»ºµÄÉıÁËÆğÀ´£¬Ô½À´Ô½¸ß¡£\n\n" , me);
   switch( random(2) ) {
   case 0:
      tell_object(me, me->name()+"ÊÖÖĞµÄ"+obj->name()+"Ô½·ÉÔ½¸ß¡£ \n");
      message_vision("Ö»ÌıÒ»ÕóÇåÔÃµÄÉÚÒô´Ó¸ß¿Õ´«¹ı£¡ \n", me);
      call_out("boat_come", 2, me);
   break;
   case 1:
      message_vision("Ò»Õó¾¢·ç´µ¹ı£¬$NÊÖÖĞµÄÏß¶ÏÁË£¬"+obj->name() 
+"Ô½À´Ô½¸ß£¬ÂıÂıµÄ²»¼ûÁË¡£ \n",me);
      destruct(obj);
      break;
   }
   return; 
}

void boat_come(object me)
{
   object  boat, *inv, ob;
   int i;
        

   if (query("exits/down")) return ;
   if (!objectp(boat=find_object("/d/dragon/boat")))
      boat=load_object("/u/night/room/boat");
   inv=all_inventory(boat);
   for(i=0; i<sizeof(inv); i++) {
      ob = inv[i];
      if(living(ob)){
         message("vision","°ëÉÎ£¬ºşÉÏ»¹ÊÇÃ»ÓĞË¿ºÁ¶¯¾²¡£\n",this_object()); 
         return;
      }
   }
   message("vision","¹ıÁË°ëÉÎ£¬Ò»Ò¶Ğ¡ÖÛ»º»ºµØ´ÓÎíÖĞµ´³ö£¬¿¿µ½ÁËºş±ß¡£\n",this_object()); 
    boat->set("exits/up","/d/dragon/lake2");
  set("exits/down","/d/dragon/boat");
   call_out("boat_leave",10,boat);
   return ;
}

void boat_leave(object boat)
{
        if (query("exits/down")) delete("exits/down");
        if (boat->query("exits/up")) boat->delete("exits/up");
        message("vision","Ò»ÕóÎ¢·ç·÷¹ı£¬Ğ¡´¬µ´ÀëÁË°¶±ß¡£\n",this_object()); 
        message("vision","Ò»ÕóÎ¢·ç·÷¹ı£¬Ğ¡´¬µ´ÀëÁË°¶±ß¡£\n",boat); 
        return;
}

int valid_leave(object me, string dir)
{
   object *inv, boat, ob;
   int i;

   if (userp(me) && dir == "down") {
      boat=find_object("/d/dragon/boat");
      if (!objectp(boat))
         boat=load_object("/d/dragon/boat");
         inv=all_inventory(boat);
            for(i=0; i<sizeof(inv); i++) {
               ob = inv[i];
               if(living(ob)){
                  tell_object(me, "´¬Ì«Ğ¡ÁË£¬Ö»ÄÜ³Ë×øÒ»¸öÈË¡£\n");      
                  return notify_fail("");
               }
           }
   }
   return 1;
}

