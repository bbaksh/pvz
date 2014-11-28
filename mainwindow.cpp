#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pvz=ui->graphicsView;
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
    }
    else
        pvz->setCurrentUser();
    ui->levelDisplay->setNum(pvz->getCurrentLevel());
    ui->levelDisplay->setAlignment(Qt::AlignCenter);
    ui->pointsDisplay->setText(QString::number(pvz->getSunPoints()));
    ui->pointsDisplay->setAlignment(Qt::AlignCenter);
    ui->userButton->addItems(pvz->userSort());
    pvz->scene1 = new QGraphicsScene(this);
    ui->graphicsView->setScene(pvz->scene1);
    ui->graphicsView->resize(900,500);

    //QRectF rect(0,0,800,500);//478
    //scene->setSceneRect(rect);
    //scene->addRect(0,0,100,100);
    //scene->addPixmap(levelsPath.currentPath()+"/mainscreen.png");
    pvz->scene1->addPixmap(pvz->mainScreen());
    ui->graphicsView->adjustSize();
    //this->connect(this,SIGNAL(mouseclick(QEvent*)),this,SLOT(handleclick(QEvent*)));

    timer = new QTimer(this);
    this->connect(timer, SIGNAL(timeout()), pvz, SLOT(dropSun()));

    updateSuns = new QTimer(this);
    this->connect(updateSuns,SIGNAL(timeout()),this,SLOT(updateSunLabel()));

   // pvz->sunflowerTimer = new QTimer(this);

    zombieTimer = new QTimer(this);
    this->connect(zombieTimer,SIGNAL(timeout()),pvz,SLOT(spawnZombies()));

    animateZombie = new QTimer(this);
    this->connect(animateZombie,SIGNAL(timeout()),pvz,SLOT(moveZombiesAndPlants()));
   //this->connect(pvz->sunflowerTimer,SIGNAL(timeout()),pvz,SLOT(sunFlowerSun()));
   // this->connect(&(this->pvz),SIGNAL(mouse()),this,SLOT(handleclick(QEvent*)));



    //scene->addEllipse(10,10,1000,100);

//    QRectF rect(-100,-100,100,100);
//    scene->setSceneRect(rect);
//    QPen my_pen = QPen(Qt::blue);        // Draw lines with a red pen
//    scene->addLine(QLineF(rect.bottomLeft(), rect.bottomRight()) ,my_pen);
//    scene->addLine(QLineF(rect.topLeft(), rect.topRight()) ,my_pen);
//    scene->addLine(QLineF(rect.bottomLeft(), rect.topLeft()) ,my_pen);
//    scene->addLine(QLineF(rect.topRight(), rect.bottomRight()) ,my_pen);
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

//bool MainWindow::event(QEvent *mouse)
//{
//     if(mouse->type()==QEvent::MouseButtonPress)
//         emit mouseclick(mouse);
//}

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
    ui->levelDisplay->setNum(pvz->getCurrentLevel());
    }
    else
        ui->nameDisplay->setPlaceholderText("Please enter a name");

}

void MainWindow::on_deleteButton_clicked()
{
    //need to get current index;
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
    timer->stop();
    quit.setFixedSize(QSize(900,300));
    quit.setFixedSize(900,300);
    //restart.setBaseSize(900,300);
    quit.setText("Are you sure you want to quit?");
    QAbstractButton *okayButton =quit.addButton(tr("OKAY"),QMessageBox::ActionRole);
    QAbstractButton *cancelButton =quit.addButton(tr("CANCEL"),QMessageBox::ActionRole);
    //quit.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    quit.exec();
    if(quit.clickedButton() == okayButton)
    {
        pvz->scene1->clear();
        pvz->scene1->addPixmap(pvz->mainScreen());
        ui->graphicsView->adjustSize();
    }
    if(quit.clickedButton()==cancelButton)
    {
        //timer->start();
        std::cout<<"test"<<std::endl;
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
    //ui->startButton->hide();
    updateSuns->start(20);
    timer->start(10000);//10000ms is 10 seconds
    zombieTimer->start(1000);
    animateZombie->start(25);
    pvz->scene1->clear();
    pvz->setLevel(pvz->getRows(pvz->getCurrentLevel()));
    //pvz->setLevel(pvz->getCurrentLevel());
    ui->graphicsView->adjustSize();
    QApplication::processEvents();



}

void MainWindow::on_restartButton_clicked()
{
    timer->stop();
    QMessageBox restart;

    restart.setFixedSize(QSize(900,300));
    restart.setFixedSize(900,300);
    //restart.setBaseSize(900,300);
    restart.setText("Are you sure you want to restart?");
    restart.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    restart.exec();
    if(restart.button(QMessageBox::Ok))
    {

    }
    if(restart.button(QMessageBox::Cancel))
    {

    }
}

void MainWindow::updateSunLabel()
{
    ui->pointsDisplay->setText(QString::number(pvz->getSunPoints()));
    ui->graphicsView->scene()->update();
}

void MainWindow::on_plant1Button_clicked()
{
    if(pvz->getSunPoints()>=100)
    {
    pvz->setPlantType(1);
    }

}

void MainWindow::on_plant2Button_clicked()
{
    if(pvz->getSunPoints()>=50)
    pvz->setPlantType(2);
}

void MainWindow::on_plant3Button_clicked()
{
    if(pvz->getSunPoints()>=150)
    pvz->setPlantType(3);
}

void MainWindow::on_plant4Button_clicked()
{
    if(pvz->getSunPoints()>=50)
    pvz->setPlantType(4);
}

void MainWindow::on_plant5Button_clicked()
{
    if(pvz->getSunPoints()>=25)
    pvz->setPlantType(5);
}

void MainWindow::on_plant6Button_clicked()
{
    if(pvz->getSunPoints()>=175)
    pvz->setPlantType(6);
}

void MainWindow::on_plant7Button_clicked()
{
    if(pvz->getSunPoints()>=150)
    pvz->setPlantType(7);
}

void MainWindow::on_plant8Button_clicked()
{
    if(pvz->getSunPoints()>=200)
    pvz->setPlantType(8);
}
