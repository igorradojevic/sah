#ifndef POLJE_H
#define POLJE_H

#include<QGraphicsRectItem>
#include<QBrush>
#include<QGraphicsSceneMouseEvent>

class Polje: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Polje(QGraphicsItem *parent=NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void grafikaPostaviBoju(QColor boja);
    void grafikaZasijajPolje();
    void grafikaOdsijajPolje();

    int getX() const
    {
        return _x;
    }

    int getY() const
    {
        return _y;
    }

    void setX(int x)
    {
        _x = x;
    }
    void setY(int y)
    {
        _y = y;
    }
signals:
    void clicked();

private:
    QBrush cetkica;
    int _x;
    int _y;

};

#endif // POLJE_H
