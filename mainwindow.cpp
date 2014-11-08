#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QDir playersPath;
    QDir levelsPath;
    pvz.readLevelData(levelsPath.currentPath()+"/pvz_levels.csv");
    pvz.readUserData(playersPath.currentPath()+"/pvz_players.csv");
    //pvz.createUser("bob");
    //pvz.createUser("Brandon");
    //pvz.saveUsers(playersPath.currentPath()+"/pvz_players.csv");



    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(pvz.getCurrentScreen());
    //scene->setSceneRect(0,0,pvz.getCurrentScreen().width(),pvz.getCurrentScreen().height());
    //ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatioByExpanding);
}

MainWindow::~MainWindow()
{
    delete ui;
}
