#include "jvim.hpp"

jvim::jvim(const std::string &file)
{
    x = y = 0;
    mode = 'n';
    status = "  NORMAL  ";
    section = {};

    if (file.empty())
    {
    }
    else
    {
    }

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    use_default_colors();
    start_color();
}

jvim::~jvim()
{
    refresh();
    endwin();
}

void jvim::run()
{
    while (mode)
    {
        update();
        statusLine();
        print();
        int c = getch();
        input(c);
    }
}

void jvim::update()
{
    switch (mode)
    {
    case 'n':
        status = "  NORMAL  ";
        break;
    case 'q':
    default:
        break;
    }
}
