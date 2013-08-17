#include <iostream>

template <typename T>
T get_max(T a, T b)
{
	return a > b ? a : b;
}

int main(void)
{
	int a = 3, b = 5;
	std::cout<<"max of "<<a<<" and "<<b<<" is: "<<get_max(a, b)<<std::endl;
	return 0;
}
