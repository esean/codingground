#include <iostream>
#include <string>

using namespace std;

// For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4]

string rotate_by(string str, int k)
{
	int sz = str.size();
	// make sure we don't do extra work
	int actual_shift;
	if (k>0) actual_shift = (k % sz)+1;
	string s1 = str.substr(actual_shift,sz-actual_shift);
	string s2 = str.substr(0,actual_shift);
	return s1 + s2;
}

void rotate_byC(const char* str, int k, char* ret)
{
	const char *s = str;
	char *d = ret;
	int sz = strlen(str);
	// make sure we don't do extra work
	int actual_shift;
	if (k>0) actual_shift = (k % sz)+1;
	while (actual_shift) {
		++s; --actual_shift;
	}
	while((d-ret) < sz) {
		*d++ = *s++;
		if ((s-str) >= sz) s=str;
	}
}

void print_int_array(int* arr, int sz)
{
	printf("INT_ARRAY[%d]:",sz);
        for (int i=0; i<sz; ++i)
                printf("%d,",arr[i]);
        printf("\n");
}

void reverse(int* num, int left, int right)
{
	int* s = num + left;
	int* e = num + right;
	while (s < e)
	{
		int tmp = *s;
		*s = *e;
		*e = tmp;
		++s; --e;
	}
}

void rotate_array(int* numarr, int sz, int k)
{
	reverse(numarr,0,sz-1);
	reverse(numarr,0,k-1);
	reverse(numarr,k,sz-1);
}

int main()
{
	string msg = "1234567";
	string ret = rotate_by(msg,3);
	cout << "msg=" << msg << " => " << ret << endl;

	const char msg2[] = "1234567";
	char ret2[128];
	rotate_byC(msg2,3,ret2);
	cout << "msg=" << string(msg2) << " => " << string(ret2) << endl;
	
	int msg3[] = {1,2,3,4,5,6,7};
	rotate_array(msg3,sizeof(msg3)/sizeof(msg3[0]),3);
	print_int_array(msg3,sizeof(msg3)/sizeof(msg3[0]));

  	return 0;
}

