#include "spherewiew.h"
#include <QGraphicsRectItem>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

SphereWiew::SphereWiew(QWidget *parent) : QGraphicsView(parent), x(0), y(0)
{
    //this->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    _scene = new QGraphicsScene;
    //_scene->setSceneRect(QRectF(0, 0, this->width(), this->height()));
    this->setScene(_scene);

    _group = _scene->createItemGroup(QList<QGraphicsItem*>());
    _group->setX(30);
}

SphereWiew::~SphereWiew()
{
    _scene->destroyItemGroup(_group);
}

void SphereWiew::addItem(QString name, bool status)
{
    QPen pen;
    pen.setCosmetic(true);

    QGraphicsRectItem* item = new SphereItem(name, QRectF(x, y, ITEM_SIZE, ITEM_SIZE));
    item->setPen(pen);

    if(status)
        item->setBrush(QBrush(QColor(Qt::green)));
    else
        item->setBrush(QBrush(QColor(Qt::red)));
    //item->setOpacity(0.5);
    _group->addToGroup(item);

    y += ITEM_SIZE + 10;

}

// --------------------------------

SphereItem::SphereItem(const QString &name, const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent),
      _name(name)
{

}

void SphereItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option);


    QPen pen;
    pen.setColor(Qt::black);

    QRectF rec = option->exposedRect;

    qDebug() << "rec.x = " << rec.x() << "rec.y = " << rec.y();

    painter->setPen(pen);
    painter->drawText(QRectF(rec.x() + 10, rec.y() + 10, rec.height(), rec.width()), _name);
    //painter->drawImage(rec.x() + 10, rec.y() + 10, QImage(":/images/images/antenna.png"));


}

