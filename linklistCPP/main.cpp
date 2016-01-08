#include <iostream>
#include <stdbool.h>

using namespace std;

class node {
	public:
		node() { value=0; pNext=NULL; }
		node(int v) { value=v; pNext=NULL; }
		~node() {}

		void dump() {
			dumper(this);
		}
		void set_value(int val) {
			this->value = val;
		}
		void add_node(node* pNode) {
			this->pNext = pNode;
		}
		bool is_circular();
	private:
		node* pNext;
		int value;
		void dumper(node* start);
};

void node::dumper(node* start) {
	int i = 0;
	printf("%d:%d\n",i,start->value);
	while (start->pNext)
	{
		++i;
		start = start->pNext;
		printf("%d:%d\n",i,start->value);
	}
}
bool node::is_circular() {
	node* n1 = this;
	node* n2 = this;
	if (!n1) return false;
	n2 = n2->pNext;
	while (n1) {
		if (n1==n2) return true;
		if (!n1 || !n2) return false;
		n1 = n1->pNext;
		n2 = n2->pNext->pNext;
	}
}

int main()
{
    node first(1);
    node second(2);
    node third(3);

    first.add_node(&second);
    second.add_node(&third);
  
    printf("Before making circular:\n");
    first.dump();

    // make circular
    third.add_node(&first);

    // NO! - don't call
    //first.dump();

    printf("Buffer is %s circular\n", first.is_circular() ? "YES" : "NOT");

   return 0;
}
