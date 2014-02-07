#include <cstdio>
#include <iostream>

class MyClass {
public:
	int my_mul(int a, int b) { return a + b; }
};

int add(int a, int b)
{
	return a + b;
}

int (*f) (int, int);
int (MyClass::*g) (int, int);

int main(void)
{
	MyClass c;
	f = add;
	g = &MyClass::my_mul;
	std::cout<<f(1,1)<<std::endl;
	std::cout<<(c.*g)(1,1)<<std::endl;
	return 0;
}
