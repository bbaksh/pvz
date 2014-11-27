#ifndef BULLETS_H
#define BULLETS_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QDir>
class Bullets: public QGraphicsItem
{
public:
    Bullets();
    Bullets(int type,int xPos, int yPos);
    int getX();
    int getY();
    int getDamage();
    void setPosition(int x, int y);
    void slideBullet();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    void advance(int);
private:
    int damage;
    int type;
    int xPos;
    int yPos;
    QDir file;
    QPixmap bulletPicture;
};

#endif // BULLETS_H
