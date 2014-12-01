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
    int getType();//type of plant that makes a bullet
    int getDamage();
    void setPosition(int x, int y);
    void slideBullet();//used to translate the bullet across the scene (like advance)
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    void advance(int);
private:
    int damage;
    int type;
    int xPos;
    int yPos;
    QDir file;//used to get the homepath for the pixmap
    QPixmap bulletPicture;//used to store the picture
};

#endif // BULLETS_H
