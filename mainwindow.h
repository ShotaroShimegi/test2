#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <drawmaze.h>
#include <simulatemazerun.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Switch_clicked();

    void on_load_botton_clicked();

    void on_drawMazeButton_clicked();

    void on_Drawmaze_clicked();

    void on_Simulate_clicked();

    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;

    void init();    //自分で追加したよ
    void loadMazeData(QTextStream *maze_data, uint8_t wall_data[16][16]);

    uint8_t maze[16][16];   //既に打ち込まれた壁情報
    QGraphicsScene *scene = new QGraphicsScene;
    DrawMaze *drawmaze;
    bool maze_read = false;
    SimulateMazeRun *simulate_run;

};

#endif // MAINWINDOW_H
