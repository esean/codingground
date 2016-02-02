#include <iostream>
using namespace std;

class calculator;	// forward
typedef int (calculator::*arithmeticFcn)(int,int);

// throws on error
class calculator {
public:
	int get_user_integer();
	char get_user_operator();

	int add(int x, int y) { return x+y; }
	int subtract(int x, int y) { return x-y; }
	int multiply(int x, int y) { return x*y; }
	int divide(int x, int y) { return x/y; }

	struct arithmeticStruct {
		char op;
		arithmeticFcn fcn;
	};
	static const int NUM_OPS = 4;
	arithmeticStruct arithmeticArray[NUM_OPS] = {
		{'+',&calculator::add},
		{'-',&calculator::subtract},
		{'*',&calculator::multiply},
		{'/',&calculator::divide},
	};

	arithmeticFcn getArithmeticFunction(char op);
	int perform_operation(int x, int y, char op);
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
arithmeticFcn calculator::getArithmeticFunction(char op) {
#if 1
	for (int idx=0; idx < NUM_OPS; ++idx) {
		if (op == arithmeticArray[idx].op)
			return arithmeticArray[idx].fcn;
	}
	throw "couldn't find that op";
#else
	switch (op) {
		case '+':	return &calculator::add;
		case '-':	return &calculator::subtract;
		case '*':	return &calculator::multiply;
		case '/':	return &calculator::divide;
			break;
		default:
			throw "invalid operator in op";
			break;
	}
#endif
}
int calculator::perform_operation(int x, int y, char op) {
	arithmeticFcn fcn = getArithmeticFunction(op);
	return (this->*fcn)(x,y);
}

int main()
{
	try {
		calculator calc;
		int x = calc.get_user_integer();
		int y = calc.get_user_integer();
		char op = calc.get_user_operator();
		int res = calc.perform_operation(x,y,op);
		cout << "You entered:" << x << op << y << " = " << res << endl;
	}
	catch(const char* error) {
		cout << "ERROR:" << error << endl;
		return 1;
	}

	return 0;
}
