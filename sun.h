#ifndef SUN_H
#define SUN_H
#include <iostream>
#include <QPainter>
#include <QPicture>

#include <QGraphicsItem>

class Sun : public QGraphicsItem
{
private:
    int xPos;
    int yPos;
    QPixmap sunPicture;
public:
    Sun();
    Sun(int x, int y,QString path);
    int getX();
    int getY();
    void setClicked();

    void advance(int phase);
    bool areaX(int x);
    bool areaY(int y);
    QPixmap getPicture();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SUN_H
