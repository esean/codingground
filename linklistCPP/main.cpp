#include <iostream>
#include <stdbool.h>

using namespace std;

template<class T>
class node {
	public:
		node() { pNext=NULL; }
		node(T v) { value=v; pNext=NULL; }
		~node() {}

		void dump() {
			dumper(this);
		}
		void set_value(T val) {
			this->value = val;
		}
		void add_node(node* pNode) {
			this->pNext = pNode;
		}
		bool is_circular();
	private:
		node* pNext;
		T value;
		void dumper(node* start);
};

template<class T> void node<T>::dumper(node<T>* start) {
	int i = 0;
	cout << i << ":" << start->value << endl;
	while (start->pNext)
	{
		++i;
		start = start->pNext;
		cout << i << ":" << start->value << endl;
	}
}
template<class T> bool node<T>::is_circular() {
	node<T>* n1 = this;
	node<T>* n2 = this;
	if (!n1) return false;
	n2 = n2->pNext;
	while (n1) {
		if (n1==n2) return true;
		if (!n1 || !n2) return false;
		n1 = n1->pNext;
		n2 = n2->pNext->pNext;
	}
	// can't get here
	return false;
}

int main()
{
    // INT
    //-----------------
    node<int> first(1);
    node<int> second(2);
    node<int> third(3);

    first.add_node(&second);
    second.add_node(&third);
  
    printf("Before making circular:\n");
    first.dump();

    // make circular
    third.add_node(&first);

    // NO! - don't call
    //first.dump();

    printf("INT Buffer is %s circular\n", first.is_circular() ? "YES" : "NOT");

    // CHAR
    //-----------------
    node<char> c1('a');
    node<char> c2('b');
    node<char> c3('c');
    c1.add_node(&c2);
    c2.add_node(&c3);
    c1.dump();
    printf("CHAR Buffer is %s circular\n", c1.is_circular() ? "YES" : "NOT");

   return 0;
}
