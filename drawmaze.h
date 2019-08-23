#ifndef DRAWMAZE_H
#define DRAWMAZE_H

#include<QtWidgets>

class DrawMaze
{
public:
    DrawMaze();
    void init(QGraphicsScene *scene);
    void drawWall(QGraphicsScene *scene,uint8_t (*wall)[16]);
    void drawMachine(QGraphicsScene *scene, uint8_t x,uint8_t y);
    void drawSimulate(QGraphicsScene *scene, uint8_t x, uint8_t y,uint8_t (*wall)[16]);

private:
    const int step = 43;
    QPen pen;
};

#endif // DRAWMAZE_H
