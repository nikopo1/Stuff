#include <iostream>
#include <new>

#include <stdlib.h>

using namespace std;

class Container {
	int a;
	int b;
public:
	Container(void): a(0), b(0) {}
};

int main(void)
{
	void* p = calloc(1000, sizeof(char));
	Container* c = new(p) Container;
	cout << "buffer address = " << (void*) p << endl;
	cout << "container address = " << (void*) c << endl;
	delete c;
#ifdef DOUBLE_FREE
	free(p);
#endif

	// char memory[sizeof(int)];
	char *memory = reinterpret_cast<char*>(calloc(4, sizeof(char)));
	memory[0] = 'd';
	memory[1] = 'e';
	memory[2] = 'a';
	memory[3] = 'd';
	int* p_int = new (memory) int;

	cout << "buffer  address = " << (void*) memory << endl;
	cout << "integer address = " << (void*) p_int << endl;

	free(memory);
	
	return 0;
}
