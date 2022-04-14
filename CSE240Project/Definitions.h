


#ifndef DEFINITION_H
#define DEFINITION_H

enum class GAME_STATE
{
   MENU,
   INIT,
   PLAY,
   PAUSE
};

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60
#define BALLWIDTH 16

struct Circle
{
    int x, y;
    int r;
};


#endif