#include <iostream>
#include <unordered_map>

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

static bool is_any_permutation_a_palindrome(string str)
{
    // if str.len is even: each char count should be even
    // is str.len is odd: same as even case, but need exactly one odd
    int len = str.size();
    
    unordered_map<char,int> char_map;
    for (int i=0; i<len; ++i)
        if (char_map[str[i]])
            ++char_map[str[i]];
        else
            char_map[str[i]] = 1;
    
    int even_cnt, odd_cnt;
    even_cnt = odd_cnt = 0;
    for (const auto &pair : char_map)
        if (pair.second%2)
            ++odd_cnt;
        else
            ++even_cnt;
    
    if (len%2)
    {
        // odd
        if (odd_cnt==1)
            return true;
        return false;
    }
    
    // even
    if (odd_cnt==0)
        return true;
    return false;
}

int main()
{
    string str = "ivicc";
    
    if (is_palindrome(str))
        printf("%s is a PALINDROME!\n",str.c_str());
    else
        printf("%s is not a PALINDROME! reversed is %s\n",
               str.c_str(),reverse_string_in_place(str).c_str());
    
    if (is_any_permutation_a_palindrome(str))
        printf("Some permutation of those letters makes a palindrome\n");
    
    return 0;
}

