#include <memory>
#include <iostream>

class Base {
    public:
        int a;

        Base(int val) : a(val) {
        }

        virtual ~Base() {
            std::cout << "Base is destroyed " << a << std::endl;
        }
};

class Derived : public Base {
    public:
        Derived(): Base(1) {
        }

        virtual ~Derived() {
            std::cout << "Derived is destroyed " << Base::a << std::endl;
        }
};

int main(void)
{
    std::shared_ptr<Base> base = std::make_shared<Derived>();

    return 0;
}
