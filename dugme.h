#ifndef DUGME_H
#define DUGME_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>


class Dugme:public QObject, public QGraphicsRectItem
{
     Q_OBJECT
public:

    Dugme(QString ime, QGraphicsItem * parent = NULL);

    //public methods

    //events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem *tekst;
};
#endif // DUGME_H
