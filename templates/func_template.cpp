#include <iostream>
#include <stdlib.h>

template <typename T>
T get_max(T a, T b)
{
	return a > b ? a : b;
}

template <typename T>
T* get_memory(void)
{
	return (T*)malloc(sizeof(T));
}

int main(void)
{
	int a = 3, b = 5;
	unsigned long long c = -1, d = 500;
	int *p;

	std::cout<<"Test 1"<<std::endl;
	std::cout<<"max of "<<a<<" and "<<b<<" is: "<<get_max(a, b)<<std::endl;
	std::cout<<"max of "<<c<<" and "<<d<<" is: "<<get_max(c, d)<<std::endl;
	std::cout<<std::endl;

#ifdef GET_TYPE_ERROR
	std::cout<<"Test 2"<<std::endl;
	std::cout<<"allocated memory value = "<<*get_memory()<<std::endl;
	std::cout<<std::endl;
#endif /* GET_TYPE_ERROR */

	p = get_memory<int>();
	std::cout<<"Test 2 bis (define GET_TYPE_ERROR for first)"<<std::endl;
	std::cout<<"allocated int value = "<<*p<<", at address "<<p<<std::endl;
	std::cout<<std::endl;

	free(p);
	return 0;
}
