#pragma once

#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

// NCURSES
#include <ncurses.h>

class JVim
{
private:
    size_t x, y;
    char mode;
    std::string status, section;
    std::vector<std::string> lines, cmds;

public:
    JVim(const std::string &);
    ~JVim();
    void run();

    void update();

protected:
    void statusLine();
    void input(int);
    void printLines();
    void printCmd();
    void upCmd();
    void downCmd();
    void endCmd();
    void homeCmd();
};
