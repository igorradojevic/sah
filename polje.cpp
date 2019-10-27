#include "polje.h"
#include "igra.h"

extern Igra *igra;

Polje::Polje(QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //pravimo kvadrat
    setRect(0,0,50,50);
    setZValue(-1);
    setAcceptHoverEvents(true);

}

void Polje::grafikaPostaviBoju(QColor boja)
{
    cetkica.setColor(boja);
    setBrush(boja);
}

void Polje::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    {
        igra->setUnetoPolje(this);
        emit clicked();
    }
}

void Polje::grafikaZasijajPolje()
{
    grafikaPostaviBoju(Qt::red);
}

void Polje::grafikaOdsijajPolje()
{
    if((_x+_y)%2 == 0)
        grafikaPostaviBoju(Qt::lightGray);
    else
        grafikaPostaviBoju(Qt::darkGray);
}
