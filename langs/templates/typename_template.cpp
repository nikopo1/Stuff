#include <iostream>

template<typename S, typename T>
class Pair {
public:
	typedef S first_type;
	typedef T second_type;

	Pair(S first, T second):
		first_(first),
		second_(second) {}

	S first() { return first_; }

	void set_first(S first) { first_ = first; }

	T second() { return second_; }

	void set_second(T second) { second_ = second; }
private:
	S first_;
	T second_;
};

/*
 * Item 42 from Effective C++
 */
template<typename K, typename V>
class Point: public Pair<K,V>::first_type {
public:
	explicit Point(int value):
		Pair<K,V>::first_type(value)
	{
		typename Pair<K,V>::first_type tmp;
	}
};

int main(void)
{
	Pair<int, float> p(5, 7.0f);

	Pair<int, float>::second_type second;
	second = p.second();

	std::cout << second << std::endl;

	return 0;
}
