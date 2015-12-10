#include <iostream>

using namespace std;

int main()
{
    int start = 3;
    string str = "Sometimes (when I nest them (my parentheticals) too much (like this (and this))) they get confusing.";
   
  // find first '('
  int real_start = start;
  if (str[real_start] != '(')
  {
      for(;real_start < str.size(); ++real_start)
      {
          if (str[real_start] == '(')
            break;
      }
  }
  
  int first = real_start;
  printf("First at %d\n",real_start);
  
  // now go find the ending one that matches this one
  int paren_cnt = 1;    // we just saw one, ie, we are inside
  ++real_start; // already found this one, step over
  for (; real_start < str.size(); ++real_start)
  {
      //printf("CH%c[%d:%d] ",str[real_start],real_start,paren_cnt);
      if (str[real_start] == '(') ++paren_cnt;
      if (str[real_start] == ')') --paren_cnt;
      
      if (paren_cnt == 0)
      {
          printf("End at %d\n",real_start);
          break;
      }
  }
  
  for (int x = first+1; x<real_start; ++x)
    printf("%c",str[x]);
  printf("\n");
   
   return 0;
}

