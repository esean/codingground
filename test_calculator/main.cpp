#include <iostream>
#include <stdbool.h>

using namespace std;

// throws on error
class calculator {
public:
	int get_user_integer();
	char get_user_operator();
	int add(int x, int y) { return x+y; }
	int subtract(int x, int y) { return x-y; }
	int multiply(int x, int y) { return x*y; }
	int divide(int x, int y) { return x/y; }
};

	
int calculator::get_user_integer() {
	int x;
	cout << "Enter an integer: ";
	cin >> x;
	if(cin.fail()) throw "input integer invalid";
	return x;
}

char calculator::get_user_operator() {
	char op;
	cout << "Enter an operation (‘+’, ‘-‘, ‘*’, ‘/’): ";
	cin >> op;
	switch (op) {
		case '+':
		case '-':
		case '*':
		case '/':
			break;
		default:
			throw "invalid operator";
			break;
	}
	return op;
}


int main()
{
	calculator calc;

	int x,y;
	char op;

	try {

		x = calc.get_user_integer();
		y = calc.get_user_integer();
		op = calc.get_user_operator();
		cout << "You entered:" << x << op << y << endl;

	}
	catch(const char* error) {
		cout << "ERROR:" << error << endl;
		return 1;
	}

	return 0;
}
