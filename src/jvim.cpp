#include "jvim.hpp"

JVim::JVim(const std::string &file)
{
    x = y = 0;
    mode = 'n';
    status = "  STARTUP  ";
    section = {};
    cmds.insert(cmds.begin(), "");

    if (file.empty())
    {
    }
    else
    {
    }

    initscr();
    raw();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    use_default_colors();
    start_color();
}

JVim::~JVim()
{
    refresh();
    endwin();
}

void JVim::run()
{
    while (mode != 'q')
    {
        update();
        statusLine();
        printLines();
        printCmd();
        input(getch());
    }
}

void JVim::update()
{
    switch (mode)
    {
    case 'n':
        status = "  NORMAL  ";
        section = "COLS:" + std::to_string(x) + " ROWS:" + std::to_string(y);
        init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
        break;
    case 'c':
        status = "  COMMAND  ";
        section = "COLS:" + std::to_string(x) + " ROWS:" + std::to_string(y);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        break;
    default:
        break;
    }
}

void JVim::statusLine()
{
    init_color(8, 200, 200, 200);
    init_pair(1, COLOR_WHITE, 8);

    // Preenchimento da linha com o fundo
    attron(COLOR_PAIR(1));
    for (size_t i = 0; i < (size_t)COLS; i++)
    {
        mvprintw(LINES - 3, i, " ");
    }
    attroff(COLOR_PAIR(1));

    attron(A_REVERSE);
    attron(COLOR_PAIR(2));
    mvprintw(LINES - 3, 0, status.c_str());
    attroff(COLOR_PAIR(2));
    attroff(A_REVERSE);

    attron(COLOR_PAIR(1));
    mvprintw(LINES - 3, 15, section.c_str());
    attroff(COLOR_PAIR(1));
}

void JVim::input(int c)
{

    // TODO: Move keys behavior

    switch (mode)
    {
    case 27:
    case 'n':
        switch (c)
        {
        case 'c':
        case 'q':
            mode = c;
        default:
            break;
        }
        break;
    case 'c':
        switch (c)
        {
        case 27:
            mode = 'n';
            break;
        case 127:
        case KEY_BACKSPACE:
            if (x > 0)
            {
                cmds[y].erase(--x, 1);
            }
            break;
        case 10:
        case KEY_ENTER:
            ++y;
            cmds.insert(cmds.begin() + y, "");
            x = 0;
            break;
        case KEY_UP:
            upCmd();
            break;
        case KEY_DOWN:
            downCmd();
            break;
        case KEY_END:
            endCmd();
            break;
        case KEY_HOME:
            homeCmd();
            break;

        default:
            cmds[y].insert(x, 1, c);
            ++x;
            break;
        }
        break;

    // TODO: Comand mode
    default:
        break;
    }
}

void JVim::printLines()
{
    if (!lines.empty())
    {
        for (size_t i{}; i < (size_t)LINES - 1; ++i)
        {
            if (i >= lines.size())
            {
                move(i, 0);
                clrtoeol();
            }
            else
            {
                mvprintw(i, 0, lines[i].c_str());
            }
            clrtoeol();
        }
        move(y, x);
    }
}

void JVim::printCmd()
{
    if (!cmds.empty())
    {
        mvprintw(LINES - 2, 0, cmds[y].c_str());
        move(LINES - 2, cmds[y].length());
        clrtoeol();
    }
}

void JVim::upCmd()
{
    if (y > 0)
    {
        --y;
    }
    if (x >= cmds[y].length())
    {
        x = cmds[y].length();
    }
    move(LINES - 2, x);
}

void JVim::downCmd()
{
    if (y < cmds.size() - 1)
    {
        ++y;
    }

    if (x >= cmds[y].length())
    {
        x = cmds[y].length();
    }
    move(LINES - 2, x);
}

void JVim::endCmd()
{
    x = cmds[y].length();
}

void JVim::homeCmd()
{
    x = 0;
}