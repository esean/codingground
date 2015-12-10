#include <iostream>

using namespace std;

static void swap_str(string& msg,int from,int to)
{
    for (; from<to; ++from,--to)
    {
        char t = msg[from];
        msg[from] = msg[to];
        msg[to] = t;
    }
}

int main()
{
   string message = "find you will pain only go you recordings security the into if";
   
   // reverse in place
    swap_str(message,0,message.size()-1);

    // now reverse each word, seperated by spaces
    int s=0;
    int e=0;
    bool done = false;
    while (!done)
    {
        if (message[e] == ' ' || !message[e])
        {
            swap_str(message,s,e-1);
            if (!message[e]) done = true;
            ++e; // advance over space
            s = e;
        }
        ++e;
            
    }
    
    printf("MSG=%s\n",message.c_str());
   
   return 0;
}

