#include "snake.h"
#include <ncurses.h>

CSnake::CSnake(CRect r, char _c): CFramedWindow(r, _c), StartMsg(true), LastDir(KEY_RIGHT), GameOver(false), Fruit(geom.topleft.x + 6, geom.topleft.y + 6), Pause(false), res(0)
{
    CPoint b;
    b.x = 1;
    b.y = 1;
    SnakePos.push_back(b);
}

void CSnake::paint()
{
    CFramedWindow::paint();
    gotoyx(geom.topleft.y - 1, geom.topleft.x);
    printl("| LEVEL: %d |", res % 3);

    if (GameOver)
    {
        gotoyx(geom.topleft.y + 3, geom.topleft.x + 3);
        printl("Game over     Result: %d", res);
    }
    else if (StartMsg)
    {
        int x = geom.topleft.x + 4;
        int y = geom.topleft.y + 3;
        gotoyx(y, x);
        printl("h - toggle help information");
        y = geom.topleft.y + 4;
        gotoyx(y, x);
        printl("p - toggle pause/play mode");
        y = geom.topleft.y + 5;
        gotoyx(y, x);
        printl("r - restart game");
        y = geom.topleft.y + 6;
        gotoyx(y, x);
        printl("arrows - move snake (in play mode) or");
        y = geom.topleft.y + 7;
        gotoyx(y, x);
        printl("or move window (in pause mode)");
        y = geom.topleft.y + 8;
        gotoyx(y, x);
        printl("q - leave game");
    }
    else
    {
        for (int i = 1; i <(int) SnakePos.size(); ++i) {
            if (SnakePos[0].x == SnakePos[i].x && SnakePos[0].y == SnakePos[i].y)
            {
                GameOver = true;
            }
        }


        if (SnakePos[0].x == Fruit.x && SnakePos[0].y == Fruit.y)
        {
            srand(time(nullptr));
            Fruit.x = (rand() % (geom.size.x - 3)) + 1;
            Fruit.y = (rand() % (geom.size.y - 3)) + 1;
            CPoint c;
            if (SnakePos.size() > 1)
            {
                if (SnakePos[SnakePos.size() - 1].x == SnakePos[SnakePos.size() - 2].x)
                {
                    c.x = SnakePos[SnakePos.size() - 1].x;
                    if (SnakePos[SnakePos.size() - 1].y > SnakePos[SnakePos.size() - 2].y) c.y = SnakePos[SnakePos.size() - 1].y + 1;
                    else c.y = SnakePos[SnakePos.size() - 1].y - 1;
                }
                else
                {
                    c.y = SnakePos[SnakePos.size() - 1].y;
                    if (SnakePos[SnakePos.size() - 1].x > SnakePos[SnakePos.size() - 2].x) c.y = SnakePos[SnakePos.size() - 1].x + 1;
                    else c.y = SnakePos[SnakePos.size() - 1].x - 1;
                }
            }
            else
            {
                switch (LastDir)
                {
                    case KEY_UP:
                        c.x = SnakePos[0].x;
                        c.y = SnakePos[0].y + 1;
                        break;
                    case KEY_DOWN:
                        c.x = SnakePos[0].x;
                        c.y = SnakePos[0].y - 1;
                        break;
                    case KEY_RIGHT:
                        c.x = SnakePos[0].x - 1;
                        c.y = SnakePos[0].y;
                        break;
                    case KEY_LEFT:
                        c.x = SnakePos[0].x + 1;
                        c.y = SnakePos[0].y;
                        break;
                }
            }
            SnakePos.push_back(c);
            res += 1;
        }
        gotoyx(Fruit.y + geom.topleft.y, Fruit.x + geom.topleft.x);
        printl("0");
        for (int i = 0; i <(int) SnakePos.size(); ++i)
        {
            if (SnakePos[i].y == geom.size.y - 1) SnakePos[i].y = 1;
            if (SnakePos[i].x == geom.size.x - 1) SnakePos[i].x = 1;
            if (SnakePos[i].y == 0) SnakePos[i].y = geom.size.y - 2;
            if (SnakePos[i].x == 0) SnakePos[i].x = geom.size.x - 2;
            gotoyx(SnakePos[i].y + geom.topleft.y, SnakePos[i].x + geom.topleft.x);
            if (i == 0) printl("*");
            else printl("+");
        }
        if (!Pause){
            int dly;
            if (res % 3 == 0) dly = 350;
            else dly = 350 - ((res % 3) * 25);
            napms(dly);
            AutoMove();
        }
    }
}

bool CSnake::handleEvent(int key)
{
    if (key == 'p')
    {
        Pause = !Pause;
        return true;
    }
    if (key == 'h')
    {
        StartMsg = !StartMsg;
        return true;
    }
    if (key == 'r')
    {
        GameOver = false;
        StartMsg = true;
        SnakePos.clear();
        CPoint b;
        b.x = 1;
        b.y = 1;
        SnakePos.push_back(b);
        Fruit.x = geom.topleft.x + 6;
        Fruit.y = geom.topleft.y + 6;
        return true;
    }
    if (!StartMsg && !Pause)
    {
        switch (key)
        {
            case KEY_DOWN:
                if (LastDir != KEY_UP){
                    LastDir = KEY_DOWN;
                }
                return true;
            case KEY_UP:
                if (LastDir != KEY_DOWN){
                    LastDir = KEY_UP;
                }
                return true;
            case KEY_RIGHT:
                if (LastDir != KEY_LEFT){
                    LastDir = KEY_RIGHT;
                }
                return true;
            case KEY_LEFT:
                if (LastDir != KEY_RIGHT){
                    LastDir = KEY_LEFT;
                }
                return true;
        }
    }
    return CFramedWindow::handleEvent(key);
}





void CSnake::AutoMove()
{
    switch (LastDir)
    {
        case KEY_DOWN:
            for (int i = SnakePos.size() - 1; i > 0; --i) {
                SnakePos[i] = SnakePos[i - 1];
            }
            SnakePos[0].y += 1;
            break;
        case KEY_UP:
            for (int i = SnakePos.size() - 1; i > 0; --i) {
                SnakePos[i] = SnakePos[i - 1];
            }
            SnakePos[0].y -= 1;
            break;
        case KEY_RIGHT:
            for (int i = SnakePos.size() - 1; i > 0; --i) {
                SnakePos[i] = SnakePos[i - 1];
            }
            SnakePos[0].x += 1;
            break;
        case KEY_LEFT:
            for (int i = SnakePos.size() - 1; i > 0; --i) {
                SnakePos[i] = SnakePos[i - 1];
            }
            SnakePos[0].x -= 1;
            break;
    }
}
