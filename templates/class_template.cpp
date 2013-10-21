#include <vector>
#include <iostream>

template<typename T, class K>
class pair
{
	T first_;
	K second_;
public:
	pair(T first, T second):
		first_(first),
		second_(second)
		{}
	~pair() {}

	T get_first(void) { return first_; }
	K get_second(void) { return second_; }
};



int main(void)
{
	int a = 1;
	char b = 0x41;
	pair<int, char> p(a, b);
	std::cout<<"first = "<<p.get_first()<<", second = "<<p.get_second();
	std::cout<<std::endl;
	return 0;
}
