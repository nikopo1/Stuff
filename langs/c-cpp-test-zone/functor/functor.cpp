// Example program
#include <iostream>
#include <string>
#include <algorithm>

struct MyFunctor {
    std::locale mylocale;

    MyFunctor() : mylocale("en_US.utf8") {}
};

int main()
{
    std::string a = "abc";
    std::string b = "ABC";
    std::string aa = "ăbc";
    std::string bb = "ĂBC";

    std::transform(a.begin(), a.end(), a.begin(), ::toupper);
    std::cout << (a == b) << std::endl;

    std::transform(aa.begin(), aa.end(), aa.begin(), (std::toupper));
    std::cout << (aa == bb) << std::endl;
}
