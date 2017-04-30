#include <iostream>
#include "sample.h"

Entry::Entry(std::string key, bool readonly) :
    key_(key),
    readonly_(readonly)
{
    std::cout << key << " " << readonly << std::endl;
}

Entry::Entry(std::string key, std::string value, bool readonly) :
    key_(key),
    value_(value),
    readonly_(readonly)
{
}

std::string Entry::key() const
{
    return key_;
}

std::string Entry::value() const
{
    return value_;
}

bool Entry::readonly() const
{
    return readonly_;
}

const Entry a("a_key");
const Entry b("b_key", "b_value");
const Entry c("c_key", "c_value", false);

int main(void)
{
    std::cout << a.key() << " " << a.value() << std::endl;
    std::cout << b.key() << " " << b.value() << std::endl;
    std::cout << c.key() << " " << c.value() << std::endl;
    return 0;
}
