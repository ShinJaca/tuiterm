#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

// NCURSES
#include <ncurses.h>

class jvim
{
private:
    size_t x, y;
    char mode;
    std::string status, section;
    std::vector<std::string> lines, cmds;

public:
    jvim(const std::string &);
    ~jvim();
    void run();

    void update();

protected:
    void statusLine();
    void input(int);
    void print();
};
