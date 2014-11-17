#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QDir playersPath;
    QDir levelsPath;
    userPathName=playersPath.currentPath()+"/pvz_players.csv";
    pvz.readLevelData(levelsPath.currentPath()+"/pvz_levels.csv");
    pvz.readUserData(playersPath.currentPath()+"/pvz_players.csv");
    ui->userButton->addItems(pvz.userSort());
}

MainWindow::~MainWindow()
{
    delete ui;
    pvz.saveUsers(userPathName);
}

void MainWindow::on_newButton_clicked()
{
    if(ui->nameDisplay->text()!=""&&ui->nameDisplay->text()!="Please enter a name")
    {
    pvz.createUser(ui->nameDisplay->text());
    pvz.saveUsers(userPathName);
    ui->userButton->clear();
    ui->userButton->addItems(pvz.userSort());
    ui->nameDisplay->clear();
    }
    else
        ui->nameDisplay->setText("Please enter a name");

}

void MainWindow::on_deleteButton_clicked()
{
    //need to get current index;
    //pvz.deleteUser();
}

void MainWindow::on_quitButton_clicked()
{

}
