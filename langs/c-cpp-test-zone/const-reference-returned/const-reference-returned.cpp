#include <memory>

class Component {
    public:
        int value;
};

class SystemData {
    public:
        Component base;
        Component helper;
};

class System {
    public:
        Component& get_base() const { return data->base; }
        Component& get_helper() const { return data->helper; }

    private:
        std::shared_ptr<SystemData> data;
};

int main(void)
{
    System system;

    system.get_base().value = 1;

    return 0;
}
