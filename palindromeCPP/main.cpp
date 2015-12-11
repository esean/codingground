#include <iostream>

using namespace std;

static string reverse_string_in_place(string str)
{
    int start = 0;
    int end = str.size()-1;
    for (; start<end; ++start,--end)
    {
        char t = str[start];
        str[start] = str[end];
        str[end] = t;
    }
    return str;
}

static bool is_palindrome(string str)
{
    if (str == reverse_string_in_place(str))
        return true;
    return false;
}

int main()
{
   string str = "alison";
   
   if (is_palindrome(str))
        printf("%s is a PALINDROME!\n",str.c_str());
    else
        printf("%s is not a PALINDROME! reversed is %s\n",
            str.c_str(),reverse_string_in_place(str).c_str());
    
   return 0;
}

