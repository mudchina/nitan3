// SN:A=kGKih_o7K8S`G_
// cruise-ob.c

#include "/clone/misc/cruise-ob.h"

string long() 
{
        string msg; 
        
        msg = query("long"); 
        msg += "这是正面全裸(Koksaver)的漫游传送包。
";
        msg += extra_long();
        
        return sort_string(msg, 64, 0); 
}

