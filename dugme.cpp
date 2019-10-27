#include "dugme.h"
#include <QGraphicsTextItem>
#include <QBrush>

Dugme::Dugme(QString ime, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //crtanje pravougaonika
    setRect(0,0,200,80);
    QBrush cetkica;
    cetkica.setStyle(Qt::SolidPattern);
    cetkica.setColor(Qt::darkRed);
    setBrush(cetkica);

    //tekst
    tekst = new QGraphicsTextItem(ime,this);
    int xPoz = rect().width()/2 - tekst->boundingRect().width()/2;
    int yPoz = rect().height()/2 - tekst->boundingRect().height()/2;
    tekst->setPos(xPoz,yPoz);
    tekst->setDefaultTextColor(Qt::white);

    //Dozvoli reagovanje na prelazak misem
    setAcceptHoverEvents(true);
}

void Dugme::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    emit clicked();

}

void Dugme::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //promeni boju
    if(event){
    QBrush cetkica;
    cetkica.setStyle(Qt::SolidPattern);
    cetkica.setColor(Qt::red);
    setBrush(cetkica);
    }
}
void Dugme::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //promeni boju
    if(event){
    QBrush cetkica;
    cetkica.setStyle(Qt::SolidPattern);
    cetkica.setColor(Qt::darkRed);
    setBrush(cetkica);
    }
}
