#include <iostream>

class Base {
	int x;
protected:
	void setX(int _x) { x = _x; }
public:
	Base(int _x): x(_x) { }
	int getX(void) { return x; }
};

class DerivedPrivate: private Base {

public:
	DerivedPrivate(int _x): Base(_x) { }
	/* works because private inheritance affects the exterior of the class */
	void modifyX(int _x) { setX(_x); }
	void printX() { std::cout<<getX()<<std::endl; }
};

int main(void)
{
	enum State {
		ceva = true + 1
	};
	std::cout<<ceva<<std::endl;
	DerivedPrivate b(3);
//	Does not work because of private inheritance
//	std::cout<<b.getX()<<std::endl;
	b.printX();
	b.modifyX(4);
//	std::cout<<b.getX()<<std::endl;
	b.printX();
	return 0;
}
