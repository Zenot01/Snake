#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "screen.h"
#include "vector"
#include <cstdlib>
#include <ctime>

class CSnake:public CFramedWindow
{
private:
    bool StartMsg;
    int LastDir;
    bool GameOver;
    CPoint Fruit;
    bool Pause;
    int res;
    vector<CPoint> SnakePos;


public:
  CSnake(CRect r, char _c = ' ');
  void paint() override;
  bool handleEvent (int key) override;
  void AutoMove();
};

#endif
