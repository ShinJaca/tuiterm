#include "jvim.hpp"

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        auto jvim = std::make_shared<JVim>(argv[1]);
        jvim->run();
    }
    else
    {
        auto jvim = std::make_shared<JVim>("");
        jvim->run();
    }

    return 0;
}
