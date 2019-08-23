#include "simulatemazerun.h"
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>

SimulateMazeRun::SimulateMazeRun() {
    draw_maze = new DrawMaze();
}

SimulateMazeRun::~SimulateMazeRun(){
    delete draw_maze;
}

void SimulateMazeRun::copyNowMazeData(uint8_t wall_data[16][16]){
    for(int x=0;x<16;x++){
        for(int y=0;y<16;y++){
            simulate_wall[x][y] = wall_data[x][y];
        }
    }
}

void SimulateMazeRun::leftHandSearch(QGraphicsScene *scene){
    uint8_t act = Front;
    wall_init();
    pos.init();

    //左手法でゴールできない場合があるので、一定回数以上で終了
    int count = 200;

    while(1){
        addSimulateWall();
        draw_maze->drawSimulate(scene,pos.x,pos.y,wall);
        act = leftHand();
        count--;
        msleep(100);

        if(gx == pos.x && gy == pos.y) break;
        if(count < 0) break;
    }
    draw_maze->drawSimulate(scene,pos.x,pos.y,wall);
}

void SimulateMazeRun::msleep(int time){
    QEventLoop loop;
    QTimer::singleShot(time,&loop,SLOT( quit() ));
    loop.exec();

}

void SimulateMazeRun::addSimulateWall(){
    wall[pos.x][pos.y] = simulate_wall[pos.x][pos.y];   //現区画の壁情報を迷路データから取得
}
