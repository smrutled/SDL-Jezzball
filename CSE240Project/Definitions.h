


#ifndef DEFINITION_H
#define DEFINITION_H

enum class GAME_STATE
{
   MENU,
   INIT,
   PLAY,
   PAUSE
};

inline int SCREEN_WIDTH = 640;
inline int SCREEN_HEIGHT = 480;
inline int FPS = 60;
inline int BALLWIDTH=16;

struct Circle
{
    int x, y;
    int r;
};


#endif