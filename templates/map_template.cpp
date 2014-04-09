#include <vector>
#include <iostream>

template<typename K, typename V>
class Map
{
/*	std::vector<K> keys; */
	std::vector<V> values;
public:
	void put(K key, V value);
	V get(K key);
	unsigned int size(void);
	void clear(void);
};


int main(void)
{
	return 0;
}
