#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    loadButtons();
    userPathName=playersPath.currentPath()+"/pvz_players.csv";
    pvz.readUserData(playersPath.currentPath()+"/pvz_players.csv");
    pvz.readLevelData(levelsPath.currentPath()+"/pvz_levels.csv");
    if(pvz.closeProgram())
    {
        QMessageBox quit;
        quit.setText("Error! “pvz_levels.csv” not found!!");
        quit.setStandardButtons(QMessageBox::Ok);
        quit.exec();
        while(true)
        {
        QApplication::quit();
        }

    }
    ui->userButton->addItems(pvz.userSort());
    ui->pointsDisplay->setText(QString::number(pvz.getSunPoints()));
    ui->pointsDisplay->setAlignment(Qt::AlignCenter);
}

void MainWindow::loadButtons()
{
    QSize plantIcon(50,80);

    QPixmap peashooterPath(levelsPath.currentPath()+"/icons/peashooter.png");
    QIcon peashooterIcon(peashooterPath);
    QPixmap sunflowerPath(levelsPath.currentPath()+"/icons/sunflower.png");
    QIcon sunflowerIcon(sunflowerPath);
    QPixmap cherrybombPath(levelsPath.currentPath()+"/icons/cherrybomb.png");
    QIcon cherrybombIcon(cherrybombPath);
    QPixmap wallnutPath(levelsPath.currentPath()+"/icons/wallnut.png");
    QIcon wallnutIcon(wallnutPath);
    QPixmap patatominePath(levelsPath.currentPath()+"/icons/potatomine.png");
    QIcon potatomineIcon(patatominePath);
    QPixmap snowpeaPath(levelsPath.currentPath()+"/icons/snowpea.png");
    QIcon snowpeaIcon(snowpeaPath);
    QPixmap chomperPath(levelsPath.currentPath()+"/icons/chomper.png");
    QIcon chomperIcon(chomperPath);
    QPixmap repeaterPath(levelsPath.currentPath()+"/icons/repeater.png");
    QIcon repeaterIcon(repeaterPath);


    ui->plant1Button->setIcon(peashooterIcon);
    ui->plant1Button->setIconSize(plantIcon);
    ui->plant1Button->setToolTip("Pea Shooter - Cost:100");

    ui->plant2Button->setIcon(sunflowerIcon);
    ui->plant2Button->setIconSize(plantIcon);
    ui->plant2Button->setToolTip("Sun Flower - Cost:50");

    ui->plant3Button->setIcon(cherrybombIcon);
    ui->plant3Button->setIconSize(plantIcon);
    ui->plant3Button->setToolTip("Cherry Bomb - Cost:150");

    ui->plant4Button->setIcon(wallnutIcon);
    ui->plant4Button->setIconSize(plantIcon);
    ui->plant4Button->setToolTip("Wall Nut - Cost:50");

    ui->plant5Button->setIcon(potatomineIcon);
    ui->plant5Button->setIconSize(plantIcon);
    ui->plant5Button->setToolTip("Potato Mine - Cost:25");

    ui->plant6Button->setIcon(snowpeaIcon);
    ui->plant6Button->setIconSize(plantIcon);
    ui->plant6Button->setToolTip("Snow Pea - Cost:175");

    ui->plant7Button->setIcon(chomperIcon);
    ui->plant7Button->setIconSize(plantIcon);
    ui->plant7Button->setToolTip("Chomper - Cost:150");

    ui->plant8Button->setIcon(repeaterIcon);
    ui->plant8Button->setIconSize(plantIcon);
    ui->plant8Button->setToolTip("Repeater - Cost:200");
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
