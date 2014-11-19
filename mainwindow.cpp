#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    loadButtons();

    ui->nameDisplay->setPlaceholderText("Please enter a name");
    userPathName=playersPath.currentPath()+"/pvz_players.csv";
    pvz.readUserData(playersPath.currentPath()+"/pvz_players.csv");
    pvz.readLevelData(levelsPath.currentPath()+"/pvz_levels.csv");
    if(pvz.closeProgram())
    {
        QMessageBox quit;
        quit.setText("Error! “pvz_levels.csv” not found!!\nThe program will run with default settings.");
        quit.setStandardButtons(QMessageBox::Ok);
        quit.exec();
    }
    else
        pvz.setCurrentUser();
    ui->levelDisplay->setNum(pvz.getCurrentLevel());
    ui->levelDisplay->setAlignment(Qt::AlignCenter);
    ui->pointsDisplay->setText(QString::number(pvz.getSunPoints()));
    ui->pointsDisplay->setAlignment(Qt::AlignCenter);
    ui->userButton->addItems(pvz.userSort());
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //QRectF rect(0,0,1000,1000);
    //scene->setSceneRect(rect);
    //scene->addPixmap(levelsPath.currentPath()+"/mainscreen.png");
    scene->addPixmap(pvz.getMainScreen());


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
    pvz.saveUsers(userPathName);
}

void MainWindow::on_newButton_clicked()
{
    if(ui->nameDisplay->text()!=""&&ui->nameDisplay->text()!="Please enter a name")
    {
    pvz.createUser(ui->nameDisplay->text());
    pvz.saveUsers(userPathName);
    pvz.setCurrentUser();
    ui->userButton->clear();
    ui->userButton->addItems(pvz.userSort());
    ui->nameDisplay->clear();
    ui->levelDisplay->setNum(pvz.getCurrentLevel());
    }
    else
        ui->nameDisplay->setPlaceholderText("Please enter a name");

}

void MainWindow::on_deleteButton_clicked()
{
    //need to get current index;
    int deleteIndex=pvz.getIndex();
    pvz.deleteUser(deleteIndex);
    pvz.saveUsers(userPathName);
    pvz.setCurrentUser();
    ui->userButton->clear();
    ui->userButton->addItems(pvz.userSort());
    ui->levelDisplay->setNum(pvz.getCurrentLevel());

}

void MainWindow::on_quitButton_clicked()
{

}



void MainWindow::on_userButton_activated(const QString &arg1)
{
    pvz.updateCurrentUser(arg1);
    ui->userButton->clear();
    ui->userButton->addItems(pvz.userSort());
    ui->nameDisplay->clear();
    ui->levelDisplay->setNum(pvz.getCurrentLevel());
}

void MainWindow::on_startButton_clicked()
{
    ui->startButton->hide();
    scene->clear();
    QPen grid = QPen(Qt::black);
    QBrush dirt= QBrush(Qt::red);
    //Create the HORIZONTAL GRID LINES
    scene->addLine(QLineF(-50,-13,847,-13));//99.6 TRANSLATES 1 SQUARE DOWN (Y)
    scene->addLine(QLineF(-50,86.6,847,86.6));
    scene->addLine(QLineF(-50,186.2,847,186.2));
    scene->addLine(QLineF(-50,285.8,847,285.8));
    scene->addLine(QLineF(-50,385.4,847,385.4));
    scene->addLine(QLineF(-50,485,847,485));

    //Create the VERTICAL GRID LINES
    scene->addLine(QLineF(-50,-13,-50,485));//89.7 TRANSLATES 1 SQUARE SIDEWAYS (X)
    scene->addLine(QLineF(39.7,-13,39.7,485));
    scene->addLine(QLineF(129.4,-13,129.4,485));
    scene->addLine(QLineF(219.1,-13,219.1,485));
    scene->addLine(QLineF(308.8,-13,308.8,485));
    scene->addLine(QLineF(398.5,-13,398.5,485));
    scene->addLine(QLineF(488.2,-13,488.2,485));
    scene->addLine(QLineF(577.9,-13,577.9,485));
    scene->addLine(QLineF(667.6,-13,667.6,485));
    scene->addLine(QLineF(757.3,-13,757.3,485));
    scene->addLine(QLineF(847,-13,847,485));
    //set colors to the grid
    scene->setBackgroundBrush(Qt::green);
    scene->addRect(-50,-13,89.7,99.6,grid,dirt);
    scene->addRect(-50,86.6,89.7,99.6,grid,dirt);
    scene->addRect(-50,186.2,89.7,99.6,grid,dirt);
    scene->addRect(-50,285.8,89.7,99.6,grid,dirt);
    scene->addRect(-50,385.4,89.7,99.6,grid,dirt);

}
