#include <iostream>
#include <stdbool.h>

using namespace std;

template<class T>
class node {
	public:
		node() { pNext=NULL; }
		node(T v) { value=v; pNext=NULL; }
		~node() {}

		virtual void dump() {
			dumper(this);
		}
		void set_value(T val) {
			this->value = val;
		}
		T get_value(void) {
			return this->value;
		}
		bool is_circular();
		node* pNext;
	private:
		T value;
		void dumper(node* start);
};
template<class T>
void node<T>::dumper(node<T>* start) {
	int i = 0;
	cout << i << ":" << start->value << endl;
	while (start->pNext)
	{
		++i;
		start = start->pNext;
		cout << i << ":" << start->value << endl;
	}
}
template<class T>
bool node<T>::is_circular() {
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

template<class T>
class stack : public node<T> {
	public:
		stack() { pHead=NULL; }
		~stack() {}
    
		node<T>* push(T value);	// return==NULL is error
		T pop(void);
    
		void dump(void);
	private:
		node<T>* pHead;
};
template<class T>
node<T>* stack<T>::push(T val)
{
	node<T>* pT = (node<T>*)malloc(sizeof(node<T>));
	if (!pT) return NULL;
	pT->set_value(val);
 
	if (!pHead) {
		pHead=pT;
		pHead->pNext = NULL;
		return pT;
	}
	pT->pNext = pHead;
	pHead = pT;
	return pT;
}
template<class T>
T stack<T>::pop(void)
{
	if (!pHead) return NULL;
	T ret = pHead->get_value();	
	node<T>* pPop = pHead;
	pHead = pHead->pNext;
	free(pPop);
	return ret;
}
template<class T>
void stack<T>::dump(void)
{
#if 0
	// TODO: it's private = can't do, friend?
	node<T>::dumper(pHead);
#else
	node<T>* start = pHead;

	int i = 0;
	cout << i << ":" << start->get_value() << endl;
	while (start->pNext)
	{
		++i;
		start = start->pNext;
		cout << i << ":" << start->get_value() << endl;
	}
#endif
}

#if 1
template<class T>
class queue: public node<T> {
	public:
    queue() { pHead=NULL; pTail=NULL; printf("TODO\n"); }
		~queue() {}
    
		bool enQ(T val);
		T deQ(void);
    
	private:
		node<T>* pHead;
		node<T>* pTail;
};
template<class T>
bool queue<T>::enQ(T val)
{
}
template<class T>
T queue<T>::deQ(void)
{
}
#endif

int main()
{
    // INT
    //-----------------
    node<int> first(1);
    node<int> second(2);
    node<int> third(3);

    first.pNext = &second;
    second.pNext = &third;
  
    printf("Before making circular:\n");
    first.dump();

    // make circular
    third.pNext = &first;

    // NO! - don't call
    //first.dump();

    printf("INT Buffer is %s circular\n", first.is_circular() ? "YES" : "NOT");

    // CHAR
    //-----------------
    node<char> c1('a');
    node<char> c2('b');
    node<char> c3('c');
    c1.pNext = &c2;
    c2.pNext = &c3;
    c1.dump();
    printf("CHAR Buffer is %s circular\n", c1.is_circular() ? "YES" : "NOT");

    // INT STACK
    //-----------------
    stack<int> istk;
    istk.push(1);
    istk.push(2);
    istk.push(3);
    printf("INT STACK:\n");
    istk.dump();

    int val;
    while ( (val = istk.pop()) != NULL)
        cout << "POP: " << val << endl;

	queue<int> Q;

    return 0;
}
