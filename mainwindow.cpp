#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pvz=ui->graphicsView;
    pvz->scene1=ui->graphicsView->scene();
    loadButtons();
    srand (time(NULL));
    ui->nameDisplay->setPlaceholderText("Please enter a name");
    userPathName=playersPath.currentPath()+"/pvz_players.csv";
    pvz->readUserData(playersPath.currentPath()+"/pvz_players.csv");
    pvz->readLevelData(levelsPath.currentPath()+"/pvz_levels.csv");
    if(pvz->closeProgram())
    {
        QMessageBox quit;
        quit.setText("Error! “pvz_levels.csv” not found!!\nThe program will run with default settings.");
        quit.setStandardButtons(QMessageBox::Ok);
        quit.exec();
       emit levelsError();
    }
    else
        pvz->setCurrentUser();
    if(pvz->getCurrentLevel()!=0)
    {
        ui->levelDisplay->setNum(pvz->getCurrentLevel());
        ui->userButton->setDisabled(false);
        ui->deleteButton->setDisabled(false);
        ui->startButton->setDisabled(false);
        ui->restartButton->setDisabled(false);
        ui->quitButton->setDisabled(false);
    }
    else
    {
        ui->levelDisplay->setText("");
        ui->userButton->setDisabled(true);
        ui->deleteButton->setDisabled(true);
        ui->startButton->setDisabled(true);
        ui->restartButton->setDisabled(true);
        ui->quitButton->setDisabled(true);
    }
    ui->levelDisplay->setAlignment(Qt::AlignCenter);
    ui->pointsDisplay->setText(QString::number(pvz->getSunPoints()));
    ui->pointsDisplay->setAlignment(Qt::AlignCenter);
    ui->userButton->addItems(pvz->userSort());
    pvz->scene1= new QGraphicsScene(this);
    ui->graphicsView->setScene(pvz->scene1);
    ui->graphicsView->resize(900,500);
    pvz->scene1->addPixmap(pvz->mainScreen());
    ui->graphicsView->adjustSize();

    timer = new QTimer(this);
    this->connect(timer, SIGNAL(timeout()), pvz, SLOT(dropSun()));
    updateSuns = new QTimer(this);
    this->connect(updateSuns,SIGNAL(timeout()),this,SLOT(updateSunLabel()));

    zombieTimer = new QTimer(this);
    this->connect(zombieTimer,SIGNAL(timeout()),pvz,SLOT(spawnZombies()));

    animateZombie = new QTimer(this);
    this->connect(animateZombie,SIGNAL(timeout()),pvz,SLOT(moveZombiesAndPlants()));
    this->connect(animateZombie,SIGNAL(timeout()),pvz,SLOT(timerTracking()));
    this->connect(pvz,SIGNAL(startNextLevel()),this,SLOT(setupNextLevel()));
    this->connect(this,SIGNAL(levelsError()),this,SLOT(close()));
    this->connect(pvz,SIGNAL(startThisLevel()),this,SLOT(on_startButton_clicked()));
    this->connect(pvz,SIGNAL(disableButton(int)),this,SLOT(handleCooldown(int)));
    }


void MainWindow::loadButtons()
{
    QSize plantIcon(50,50);

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

    ui->levelDisplay->setToolTip("Current Level");

    ui->plant1Button->setDisabled(true);
    ui->plant2Button->setDisabled(true);
    ui->plant3Button->setDisabled(true);
    ui->plant4Button->setDisabled(true);
    ui->plant5Button->setDisabled(true);
    ui->plant6Button->setDisabled(true);
    ui->plant7Button->setDisabled(true);
    ui->plant8Button->setDisabled(true);
}

void MainWindow::quitProgram()
{
    QApplication::quit();
    QApplication::quitOnLastWindowClosed();
}


MainWindow::~MainWindow()
{
    delete ui;
    pvz->saveUsers(userPathName);
}

void MainWindow::on_newButton_clicked()
{
    if(ui->nameDisplay->text()!=""&&ui->nameDisplay->text()!="Please enter a name")
    {
        pvz->createUser(ui->nameDisplay->text());
        pvz->saveUsers(userPathName);
        pvz->setCurrentUser();
        ui->userButton->clear();
        ui->userButton->addItems(pvz->userSort());
        ui->nameDisplay->clear();
        if(pvz->getCurrentLevel()!=0)
        {
            ui->levelDisplay->setNum(pvz->getCurrentLevel());
            ui->userButton->setDisabled(false);
            ui->deleteButton->setDisabled(false);
            ui->startButton->setDisabled(false);
            ui->restartButton->setDisabled(false);
            ui->quitButton->setDisabled(false);
        }
        else
        {
            ui->levelDisplay->setText("");
            ui->userButton->setDisabled(true);
            ui->deleteButton->setDisabled(true);
            ui->startButton->setDisabled(true);
            ui->restartButton->setDisabled(true);
            ui->quitButton->setDisabled(true);
        }
    }
    else
        ui->nameDisplay->setPlaceholderText("Please enter a name");

}

void MainWindow::on_deleteButton_clicked()
{
    int deleteIndex=pvz->getIndex();
    pvz->deleteUser(deleteIndex);
    pvz->saveUsers(userPathName);
    pvz->setCurrentUser();
    ui->userButton->clear();
    ui->userButton->addItems(pvz->userSort());
    ui->levelDisplay->setNum(pvz->getCurrentLevel());

}

void MainWindow::on_quitButton_clicked()
{
    QMessageBox quit;
    QSpacerItem* spacer = new QSpacerItem(600, 250,QSizePolicy::Fixed, QSizePolicy::Fixed);//785
    QGridLayout* layout = (QGridLayout*)quit.layout();
    layout->addItem(spacer, 0, 0, 0, 0);
    quit.move(473,225);
    timer->stop();
    updateSuns->stop();
    zombieTimer->stop();
    animateZombie->stop();
    quit.setFixedSize(QSize(900,300));
    quit.setFixedSize(900,300);
    quit.setText("Are you sure you want to quit?");
    QAbstractButton *okayButton =quit.addButton(tr("OKAY"),QMessageBox::ActionRole);
    QAbstractButton *cancelButton =quit.addButton(tr("CANCEL"),QMessageBox::ActionRole);
    quit.exec();
    if(quit.clickedButton() == okayButton)
    {
        this->close();
    }
    if(quit.clickedButton()==cancelButton)
    {
        updateSuns->start(20);
        timer->start(10000);//10000ms is 10 seconds
        zombieTimer->start(20000);
        animateZombie->start(20);
    }
}



void MainWindow::on_userButton_activated(const QString &arg1)
{
    pvz->updateCurrentUser(arg1);
    ui->userButton->clear();
    ui->userButton->addItems(pvz->userSort());
    ui->nameDisplay->clear();
    ui->levelDisplay->setNum(pvz->getCurrentLevel());
}

void MainWindow::on_startButton_clicked()
{
    ui->userButton->setDisabled(true);
    ui->deleteButton->setDisabled(true);
    ui->nameDisplay->setDisabled(true);
    ui->newButton->setDisabled(true);
    ui->startButton->setDisabled(true);
    ui->plant1Button->setDisabled(false);
    ui->plant2Button->setDisabled(false);
    ui->plant3Button->setDisabled(false);
    ui->plant4Button->setDisabled(false);
    ui->plant5Button->setDisabled(false);
    ui->plant6Button->setDisabled(false);
    ui->plant7Button->setDisabled(false);
    ui->plant8Button->setDisabled(false);
    updateSuns->start(100);
    timer->start(10000);//10000ms is 10 seconds
    zombieTimer->start(20000);
    animateZombie->start(20);//25
    pvz->scene1->clear();
    pvz->setLevel(pvz->getRows(pvz->getCurrentLevel()));
    ui->graphicsView->adjustSize();
    QApplication::processEvents();



}

void MainWindow::on_restartButton_clicked()
{
    QMessageBox restart;
    QSpacerItem* spacer = new QSpacerItem(600, 250,QSizePolicy::Fixed, QSizePolicy::Fixed);//785
    QGridLayout* layout = (QGridLayout*)restart.layout();
    layout->addItem(spacer, 0, 0, 0, 0);
    restart.move(473,225);
    timer->stop();
    updateSuns->stop();
    zombieTimer->stop();
    animateZombie->stop();
    restart.setText("Are you sure you want to restart?");
    QAbstractButton *okayButton =restart.addButton(tr("OKAY"),QMessageBox::ActionRole);
    QAbstractButton *cancelButton =restart.addButton(tr("CANCEL"),QMessageBox::ActionRole);
    restart.exec();
    if(restart.clickedButton() == okayButton)
    {
        pvz->levelRestart();
        pvz->scene1->clear();
        pvz->setLevel(pvz->getRows(pvz->getCurrentLevel()));
        ui->levelDisplay->setNum(pvz->getCurrentLevel());
        ui->pointsDisplay->setText(QString::number(pvz->getSunPoints()));
        ui->graphicsView->scene()->update();
        updateSuns->start(20);
        timer->start(10000);//10000ms is 10 seconds
        zombieTimer->start(20000);
        animateZombie->start(20);
    }
    if(restart.clickedButton()==cancelButton)
    {
        updateSuns->start(20);
        timer->start(10000);//10000ms is 10 seconds
        zombieTimer->start(20000);
        animateZombie->start(20);
    }
}

void MainWindow::updateSunLabel()
{
    ui->pointsDisplay->setText(QString::number(pvz->getSunPoints()));
    ui->graphicsView->scene()->update();
    if(pvz->getSunPoints()==0)
    {
            ui->plant1Button->setDisabled(true);
            ui->plant2Button->setDisabled(true);
            ui->plant3Button->setDisabled(true);
            ui->plant4Button->setDisabled(true);
            ui->plant5Button->setDisabled(true);
            ui->plant6Button->setDisabled(true);
            ui->plant7Button->setDisabled(true);
            ui->plant8Button->setDisabled(true);
    }
    if(pvz->getSunPoints()>=25&&pvz->getSunPoints()<50)
    {
            ui->plant1Button->setDisabled(true);
            ui->plant2Button->setDisabled(true);
            ui->plant3Button->setDisabled(true);
            ui->plant4Button->setDisabled(true);
            ui->plant5Button->setDisabled(false);
            ui->plant6Button->setDisabled(true);
            ui->plant7Button->setDisabled(true);
            ui->plant8Button->setDisabled(true);
    }
    if(pvz->getSunPoints()>=50&&pvz->getSunPoints()<100)
    {
            ui->plant1Button->setDisabled(true);
            ui->plant2Button->setDisabled(false);
            ui->plant3Button->setDisabled(true);
            ui->plant4Button->setDisabled(false);
            ui->plant5Button->setDisabled(false);
            ui->plant6Button->setDisabled(true);
            ui->plant7Button->setDisabled(true);
            ui->plant8Button->setDisabled(true);
    }
    if(pvz->getSunPoints()>=100&&pvz->getSunPoints()<150)
    {
            ui->plant1Button->setDisabled(false);
            ui->plant2Button->setDisabled(false);
            ui->plant3Button->setDisabled(true);
            ui->plant4Button->setDisabled(false);
            ui->plant5Button->setDisabled(false);
            ui->plant6Button->setDisabled(true);
            ui->plant7Button->setDisabled(true);
            ui->plant8Button->setDisabled(true);
    }
    if(pvz->getSunPoints()>=150&&pvz->getSunPoints()<175)
    {
            ui->plant1Button->setDisabled(false);
            ui->plant2Button->setDisabled(false);
            ui->plant3Button->setDisabled(false);
            ui->plant4Button->setDisabled(false);
            ui->plant5Button->setDisabled(false);
            ui->plant6Button->setDisabled(true);
            ui->plant7Button->setDisabled(false);
            ui->plant8Button->setDisabled(true);
    }
    if(pvz->getSunPoints()>=175&&pvz->getSunPoints()<200)
    {
            ui->plant1Button->setDisabled(false);
            ui->plant2Button->setDisabled(false);
            ui->plant3Button->setDisabled(false);
            ui->plant4Button->setDisabled(false);
            ui->plant5Button->setDisabled(false);
            ui->plant6Button->setDisabled(false);
            ui->plant7Button->setDisabled(false);
            ui->plant8Button->setDisabled(true);
    }
    if(pvz->getSunPoints()>=200)
    {
            ui->plant1Button->setDisabled(false);
            ui->plant2Button->setDisabled(false);
            ui->plant3Button->setDisabled(false);
            ui->plant4Button->setDisabled(false);
            ui->plant5Button->setDisabled(false);
            ui->plant6Button->setDisabled(false);
            ui->plant7Button->setDisabled(false);
            ui->plant8Button->setDisabled(false);
    }

    if(pvz->getCooldown(0)>=7500)
    {
        ui->plant1Button->setDisabled(false);
    }
    if(pvz->getCooldown(1)>=7500)
    {
        ui->plant1Button->setDisabled(false);
    }
    if(pvz->getCooldown(2)>=50000)
    {
        ui->plant1Button->setDisabled(false);
    }
    if(pvz->getCooldown(3)>=30000)
    {
        ui->plant1Button->setDisabled(false);
    }
    if(pvz->getCooldown(4)>=30000)
    {
        ui->plant1Button->setDisabled(false);
    }
    if(pvz->getCooldown(5)>=7500)
    {
        ui->plant1Button->setDisabled(false);
    }
    if(pvz->getCooldown(6)>=7500)
    {
        ui->plant1Button->setDisabled(false);
    }
    if(pvz->getCooldown(7)>=7500)
    {
        ui->plant1Button->setDisabled(false);
    }

//    if(pvz->getSunPoints()>=25)
//    {
//    ui->plant1Button->setDisabled(true);
//    ui->plant2Button->setDisabled(true);
//    ui->plant3Button->setDisabled(true);
//    ui->plant4Button->setDisabled(true);
//    ui->plant5Button->setDisabled(false);
//    ui->plant6Button->setDisabled(true);
//    ui->plant7Button->setDisabled(true);
//    ui->plant8Button->setDisabled(true);
//    }
//    if(pvz->getSunPoints()>=50)
//    {
//    ui->plant1Button->setDisabled(true);
//    ui->plant2Button->setDisabled(false);
//    ui->plant3Button->setDisabled(true);
//    ui->plant4Button->setDisabled(false);
//    ui->plant5Button->setDisabled(false);
//    ui->plant6Button->setDisabled(true);
//    ui->plant7Button->setDisabled(true);
//    ui->plant8Button->setDisabled(true);
//    }
//    if(pvz->getSunPoints()>=100)
//    {
//    ui->plant1Button->setDisabled(false);
//    ui->plant2Button->setDisabled(false);
//    ui->plant3Button->setDisabled(true);
//    ui->plant4Button->setDisabled(false);
//    ui->plant5Button->setDisabled(false);
//    ui->plant6Button->setDisabled(true);
//    ui->plant7Button->setDisabled(true);
//    ui->plant8Button->setDisabled(true);
//    }
//    if(pvz->getSunPoints()>=150)
//    {
//    ui->plant1Button->setDisabled(false);
//    ui->plant2Button->setDisabled(false);
//    ui->plant3Button->setDisabled(false);
//    ui->plant4Button->setDisabled(false);
//    ui->plant5Button->setDisabled(false);
//    ui->plant6Button->setDisabled(true);
//    ui->plant7Button->setDisabled(false);
//    ui->plant8Button->setDisabled(true);
//    }
//    if(pvz->getSunPoints()>=175)
//    {
//    ui->plant1Button->setDisabled(false);
//    ui->plant2Button->setDisabled(false);
//    ui->plant3Button->setDisabled(false);
//    ui->plant4Button->setDisabled(false);
//    ui->plant5Button->setDisabled(false);
//    ui->plant6Button->setDisabled(false);
//    ui->plant7Button->setDisabled(false);
//    ui->plant8Button->setDisabled(true);
//    }
//    if(pvz->getSunPoints()>=200)
//    {
//    ui->plant1Button->setDisabled(false);
//    ui->plant2Button->setDisabled(false);
//    ui->plant3Button->setDisabled(false);
//    ui->plant4Button->setDisabled(false);
//    ui->plant5Button->setDisabled(false);
//    ui->plant6Button->setDisabled(false);
//    ui->plant7Button->setDisabled(false);
//    ui->plant8Button->setDisabled(false);
//    }
//    if(pvz->getSunPoints()<25)
//    {
//        ui->plant1Button->setDisabled(true);
//        ui->plant2Button->setDisabled(true);
//        ui->plant3Button->setDisabled(true);
//        ui->plant4Button->setDisabled(true);
//        ui->plant5Button->setDisabled(true);
//        ui->plant6Button->setDisabled(true);
//        ui->plant7Button->setDisabled(true);
//        ui->plant8Button->setDisabled(true);
//    }


}


void MainWindow::setupNextLevel()
{
    timer->stop();
    updateSuns->stop();
    zombieTimer->stop();
    animateZombie->stop();
    pvz->setCurrentLevel();
    if(pvz->getCurrentLevel()==9)
    {

       pvz->setLevelForEndGame();
       pvz->scene1->clear();
       ui->levelDisplay->setNum(pvz->getCurrentLevel());
       ui->pointsDisplay->setText(QString::number(pvz->getSunPoints()));
       pvz->scene1->addPixmap(pvz->mainScreen());
       ui->graphicsView->adjustSize();
       ui->graphicsView->scene()->update();
       QMessageBox wonTheGame;
       wonTheGame.setText("CONGRATULATIONS!\nYOU HAVE WON THE GAME!");
       wonTheGame.addButton(tr("Yeah! I'm Awesome!"),QMessageBox::ActionRole);
       wonTheGame.exec();
       ui->userButton->setDisabled(false);
       ui->deleteButton->setDisabled(false);
       ui->nameDisplay->setDisabled(false);
       ui->newButton->setDisabled(false);
       ui->startButton->setDisabled(false);
    }
    else
    {
    pvz->scene1->clear();
    pvz->setLevel(pvz->getRows(pvz->getCurrentLevel()));
    ui->levelDisplay->setNum(pvz->getCurrentLevel());
    ui->pointsDisplay->setText(QString::number(pvz->getSunPoints()));
    ui->graphicsView->scene()->update();
    updateSuns->start(20);
    timer->start(10000);//10000ms is 10 seconds
    zombieTimer->start(20000);
    animateZombie->start(20);
    }

}

void MainWindow::handleCooldown(int i)
{
 switch(i)
 {
     case 1:
     {
        ui->plant1Button->setDisabled(true);
        break;
     }
     case 2:
     {
         ui->plant2Button->setDisabled(true);
         break;
     }
     case 3:
     {
         ui->plant3Button->setDisabled(true);
         break;
     }
     case 4:
     {
         ui->plant4Button->setDisabled(true);
         break;
     }
     case 5:
     {
         ui->plant5Button->setDisabled(true);
         break;
     }
     case 6:
     {
         ui->plant6Button->setDisabled(true);
         break;
     }
     case 7:
     {
         ui->plant7Button->setDisabled(true);
         break;
     }
     case 8:
     {
         ui->plant8Button->setDisabled(true);
         break;
     }
 }
}

void MainWindow::on_plant1Button_clicked()
{
    if(pvz->getSunPoints()>=100)
    {
    pvz->setPlantType(1);
    ui->plant1Button->setFlat(true);
    ui->plant2Button->setFlat(false);
    ui->plant3Button->setFlat(false);
    ui->plant4Button->setFlat(false);
    ui->plant5Button->setFlat(false);
    ui->plant6Button->setFlat(false);
    ui->plant7Button->setFlat(false);
    ui->plant8Button->setFlat(false);

    }

}

void MainWindow::on_plant2Button_clicked()
{
    if(pvz->getSunPoints()>=50)
    {
    pvz->setPlantType(2);
    ui->plant1Button->setFlat(false);
    ui->plant2Button->setFlat(true);
    ui->plant3Button->setFlat(false);
    ui->plant4Button->setFlat(false);
    ui->plant5Button->setFlat(false);
    ui->plant6Button->setFlat(false);
    ui->plant7Button->setFlat(false);
    ui->plant8Button->setFlat(false);
    }
}

void MainWindow::on_plant3Button_clicked()
{
    if(pvz->getSunPoints()>=150)\
    {
    pvz->setPlantType(3);
    ui->plant1Button->setFlat(false);
    ui->plant2Button->setFlat(false);
    ui->plant3Button->setFlat(true);
    ui->plant4Button->setFlat(false);
    ui->plant5Button->setFlat(false);
    ui->plant6Button->setFlat(false);
    ui->plant7Button->setFlat(false);
    ui->plant8Button->setFlat(false);
    }
}

void MainWindow::on_plant4Button_clicked()
{
    if(pvz->getSunPoints()>=50)
    {
    pvz->setPlantType(4);
    ui->plant1Button->setFlat(false);
    ui->plant2Button->setFlat(false);
    ui->plant3Button->setFlat(false);
    ui->plant4Button->setFlat(true);
    ui->plant5Button->setFlat(false);
    ui->plant6Button->setFlat(false);
    ui->plant7Button->setFlat(false);
    ui->plant8Button->setFlat(false);
    }
}

void MainWindow::on_plant5Button_clicked()
{
    if(pvz->getSunPoints()>=25)
    {
    pvz->setPlantType(5);
    ui->plant1Button->setFlat(false);
    ui->plant2Button->setFlat(false);
    ui->plant3Button->setFlat(false);
    ui->plant4Button->setFlat(false);
    ui->plant5Button->setFlat(true);
    ui->plant6Button->setFlat(false);
    ui->plant7Button->setFlat(false);
    ui->plant8Button->setFlat(false);
    }
}

void MainWindow::on_plant6Button_clicked()
{
    if(pvz->getSunPoints()>=175)
    {
    pvz->setPlantType(6);
    ui->plant1Button->setFlat(false);
    ui->plant2Button->setFlat(false);
    ui->plant3Button->setFlat(false);
    ui->plant4Button->setFlat(false);
    ui->plant5Button->setFlat(false);
    ui->plant6Button->setFlat(true);
    ui->plant7Button->setFlat(false);
    ui->plant8Button->setFlat(false);
    }
}

void MainWindow::on_plant7Button_clicked()
{
    if(pvz->getSunPoints()>=150)
    {
    pvz->setPlantType(7);
    ui->plant1Button->setFlat(false);
    ui->plant2Button->setFlat(false);
    ui->plant3Button->setFlat(false);
    ui->plant4Button->setFlat(false);
    ui->plant5Button->setFlat(false);
    ui->plant6Button->setFlat(false);
    ui->plant7Button->setFlat(true);
    ui->plant8Button->setFlat(false);
    }
}

void MainWindow::on_plant8Button_clicked()
{
    if(pvz->getSunPoints()>=200)
    {
    pvz->setPlantType(8);
    ui->plant1Button->setFlat(false);
    ui->plant2Button->setFlat(false);
    ui->plant3Button->setFlat(false);
    ui->plant4Button->setFlat(false);
    ui->plant5Button->setFlat(false);
    ui->plant6Button->setFlat(false);
    ui->plant7Button->setFlat(false);
    ui->plant8Button->setFlat(true);
    }
}
