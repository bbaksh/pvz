#ifndef PLANTS_H
#define PLANTS_H
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QPainter>

class Plants : public QGraphicsPixmapItem
{
private:
    QDir file;
    QPixmap plantPicture;

protected:
    int type;
    int cost;
    int life;
    int range;
    int damage;
    double rate;
    int splash;
    int slow;
    int bomb;
    double seeding;
    int sun;
    int need;
    int xPos;
    int yPos;
    bool dead;
public:
    Plants();
    Plants(int type, int xPos, int yPos);
    int getCost() const;
    int getLife() const;
    void setPosition(int x, int y);
    void loseHealth(int attack);
    int getX();
    int getY();
    int getType();
    bool getStatus();
    void setStatus(bool status);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);



};

#endif // PLANTS_H
