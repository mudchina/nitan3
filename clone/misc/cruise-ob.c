// cruise-ob.c

#include "/clone/misc/cruise-ob.h"

string long() 
{
        string msg; 
        
        msg = query("long"); 
        msg += "LONG_DESCRIPTION";
        msg += extra_long();
        
        return sort_string(msg, 64, 0); 
}

