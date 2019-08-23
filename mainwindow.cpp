#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drawmaze;
    delete simulate_run;
}



void MainWindow::on_Switch_clicked()
{
    QMessageBox *box = new QMessageBox;
    box->setText("You push START botton");
    box->exec();
}

//自分で作ったぞい
void MainWindow::init(){
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint);

    scene = new QGraphicsScene;

    ui->filePath->setReadOnly(true);
    ui->view->setReadOnly(true);

/*  ここから練習用のプログラム
    ui->filePath->setText("Hello,World");

    //マップ描画用のクラス設定 書き出し練習
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addLine(10,10,100,100);
    ui->graphicsView->setScene(scene);
    //マップに文字を表示してみるなり
    QGraphicsTextItem *text = scene->addText("Maze solver");
    text->setPos(10,10);
*/
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            maze[i][j] = 0;
        }
    }
    drawmaze = new DrawMaze();

    simulate_run = new SimulateMazeRun();
    simulate_run->setGoal(7,7);

    drawmaze->init(scene);
    ui->graphicsView->setScene(scene);

}

//第二回で作ったやつ、データの取得まで
void MainWindow::on_load_botton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Text File(*.txt);;"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,tr("Error"),tr("This System could not open File"));
            return;
        }
        ui->filePath->setText(fileName);
        QTextStream stream(&file);

//      QString data = stream.readAll();
//      ui->view->setText(data);

        //読み込んだ壁情報を配列に保存させる
        loadMazeData(&stream,maze);
        maze_read = true;

        ui->view->setText("Leading Maze Data Succeeded.");
    }else{
        ui->view->setText("No Exsit File");
    }
}

//読み込んだ壁情報を配列に格納するやつ
void MainWindow::loadMazeData(QTextStream *maze_data,uint8_t wall_data[16][16]){
    for (uint8_t x=0;x<16;x++){
        QString str = maze_data->readLine();
        QList<QString>list = str.split(" ");
        for (uint8_t y=0;y<16;y++){
            wall_data[x][y] = list[y].toInt();
        }
    }
}

void MainWindow::on_Drawmaze_clicked()
{
    drawmaze->drawWall(scene, maze);

    ui->graphicsView->setScene(scene);

    QMessageBox *box = new QMessageBox;
    box->setText("you push draw Maze Button");
    box->exec();
}

void MainWindow::on_Simulate_clicked()
{
    if(maze_read){
        simulate_run->copyNowMazeData(maze);
        simulate_run->leftHandSearch(scene);
        ui->graphicsView->setScene(scene);
    }else{
        ui->view->setText("Not include Maze Data");
    }
}

void MainWindow::on_Quit_clicked()
{
    qApp->quit();
}
