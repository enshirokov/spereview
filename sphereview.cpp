#include "sphereview.h"
#include <QGraphicsRectItem>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

SphereView::SphereView(QWidget *parent)
    : QGraphicsView(parent),
      x0(0), y0(0),
      x1(300), y1(0),
      x2(600), y2(0)
{
    //this->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    _scene = new QGraphicsScene;
    //_scene->setSceneRect(QRectF(0, 0, this->width(), this->height()));
    this->setScene(_scene);

    _group = _scene->createItemGroup(QList<QGraphicsItem*>());
    //_group->setX(30);

    setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));

//    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
//    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    //fitInView(_scene->sceneRect());

    //QRectF rec = _scene->sceneRect();
    //this->setViewportMargins(0, 0, rec.width(), rec.height());
    setRenderHints(QPainter::Antialiasing); // item smoothing

    //this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    //this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );


}

SphereView::~SphereView()
{
    _scene->destroyItemGroup(_group);
}

void SphereView::resizeEvent (QResizeEvent* event)
{
    //fitInView(_scene->sceneRect());
}

void SphereView::wheelEvent(QWheelEvent * event)
{
    int angle = event->delta();

    qDebug() << "angle = " << angle;


    if(angle > 0){

        /*
        QMatrix matrix;
        matrix.scale(1 + 0.2, 1 + 0.2);

        _group->setMatrix(matrix);
        */
        this->scale(1 + 0.2, 1 + 0.2);

    }
    else{

        /*
        QMatrix matrix;
        matrix.scale(1 - 0.2, 1 - 0.2);

        _group->setMatrix(matrix);
        */
        this->scale(1 - 0.2, 1 - 0.2);



}

    QRectF rec = _group->sceneBoundingRect();
    _scene->setSceneRect(0, 0, rec.width(), this->height());


}


void SphereView::setData(QString data)
{
    QStringList list = data.split("\n");


    for(auto x: list){

        QStringList unit = x.split(";");

        switch(unit.at(1).toInt()){
        case SphereHostType::HOST_TYPE_ARM:
            addArmItem(unit.at(0), (NetStatus)unit.at(2).toInt());
            break;
        case SphereHostType::HOST_TYPE_PAUS:
            addPausItem(unit.at(0), (NetStatus)unit.at(2).toInt());
            break;
        case SphereHostType::HOST_TYPE_MANAGER:
            addManagerItem(unit.at(0), (NetStatus)unit.at(2).toInt());
            break;
        case SphereHostType::HOST_TYPE_SERVER:
            addServerItem(unit.at(0), (NetStatus)unit.at(2).toInt());
            break;


        default:
            qDebug() << "Unknown type!";
        }
    }


    _scene->setSceneRect(_scene->itemsBoundingRect());
    //fitInView(_scene->sceneRect());
    //QRectF rec = _scene->sceneRect();
    //this->setViewportMargins(rec.x(), rec.y(), rec.width(), rec.height());



}

void SphereView::addServerItem(const QString &name, NetStatus status)
{
    QPen pen;
    pen.setCosmetic(true);

    SphereServerItem* item = new SphereServerItem(name, QRectF(x2, y2, ITEM_SIZE, ITEM_SIZE), status);
    //item->setPen(pen);
    //item->setFlag(QGraphicsItem::ItemIgnoresTransformations);

    //if(status)
    //    item->setBrush(QBrush(QColor(Qt::green)));
    //else
    //    item->setBrush(QBrush(QColor(Qt::red)));
    //item->setOpacity(0.5);

    //QGraphicsLineItem* line = new QGraphicsLineItem(x2, y2, x1, y1);
    //line->setPos(x1, y1);
    //line->moveBy(x2, y2);

    _group->addToGroup(item);
   // _group->addToGroup(line);

    y2 += ITEM_SIZE + 40;

    //_scene->setSceneRect(_scene->itemsBoundingRect());
    //fitInView(_scene->sceneRect());
    //QRectF rec = _scene->sceneRect();
    //this->setViewportMargins(rec.x(), rec.y(), rec.width(), rec.height());



}

void SphereView::addManagerItem(const QString &name, NetStatus status)
{
    QPen pen;
    pen.setCosmetic(true);

    SphereManagerItem* item = new SphereManagerItem(name, QRectF(x1, y1, ITEM_SIZE, ITEM_SIZE), status);
    //item->setPen(pen);
    //item->setFlag(QGraphicsItem::ItemIgnoresTransformations);

    //if(status)
    //    item->setBrush(QBrush(QColor(Qt::green)));
    //else
    //    item->setBrush(QBrush(QColor(Qt::red)));
    //item->setOpacity(0.5);
    _group->addToGroup(item);

    y1 += ITEM_SIZE + 40;


    //_scene->setSceneRect(_scene->itemsBoundingRect());
    //fitInView(_scene->sceneRect());
    //QRectF rec = _scene->sceneRect();
    //this->setViewportMargins(rec.x(), rec.y(), rec.width(), rec.height());
}

void SphereView::addArmItem(const QString &name, NetStatus status)
{
    QPen pen;
    pen.setCosmetic(true);

    SphereArmItem* item = new SphereArmItem(name, QRectF(x0, y0, ITEM_SIZE, ITEM_SIZE), status);
    //item->setPen(pen);
    //item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
   _group->addToGroup(item);

   /*
    QGraphicsLineItem* line = new QGraphicsLineItem(ITEM_SIZE, ITEM_SIZE/2, x1, y1);
    QPen penLine;
    penLine.setColor(Qt::green);
    penLine.setWidth(5);
    line->setPen(penLine);
    _group->addToGroup(line);

    */


   QPoint point00(200, 400); // line 0
   QPoint point01(350, 400);

   QPoint point10(400, 350); // line 1
   QPoint point11(400, 100);


   QPainterPath path;
   path.moveTo(point00);
   path.lineTo(point01);
   path.cubicTo(point01, QPoint(point01.y(), point10.x()), point10);
   path.moveTo(point10);
   path.lineTo(point11);

   //path.cubicTo(200, 300,  300, 300,  300, 200);
   //path.cubicTo(300, 200,  300, 100,  400, 100);

   QGraphicsPathItem* p = new QGraphicsPathItem(path);
   QPen pen2;
   //pen2.setColor(QColor(71, 176, 43));
   //pen2.setColor(Qt::white);
   pen2.setWidth(10);
   pen2.setCosmetic(true);
   p->setPen(pen2);
   //p->setFlag(QGraphicsItem::ItemIgnoresTransformations);

   _group->addToGroup(p);



    y0 += ITEM_SIZE + 40;

    //_scene->setSceneRect(_scene->itemsBoundingRect());
    //fitInView(_scene->sceneRect());
    //QRectF rec = _scene->sceneRect();
    //this->setViewportMargins(rec.x(), rec.y(), rec.width(), rec.height());

}

void SphereView::addPausItem(const QString &name, NetStatus status)
{
    QPen pen;
    pen.setCosmetic(true);

    SpherePausItem* item = new SpherePausItem(name, QRectF(x0, y0, ITEM_SIZE, ITEM_SIZE), status);
    //item->setPen(pen);
    //item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
     _group->addToGroup(item);

   // QGraphicsLineItem* line = new QGraphicsLineItem(x0 + ITEM_SIZE/2, y0 + ITEM_SIZE/2, x1, y1);
   // _group->addToGroup(line);

    y0 += ITEM_SIZE + 40;


    //_scene->setSceneRect(_scene->itemsBoundingRect());
    //fitInView(_scene->sceneRect());
    //QRectF rec = _scene->sceneRect();
    //this->setViewportMargins(rec.x(), rec.y(), rec.width(), rec.height());
}

// SphereServerItem --------------------------------

SphereServerItem::SphereServerItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      _name(name),
      _status(status),
      _rec(rect)
{

    QString pictureName = "";

    if(_status == NetStatus::NET_STATUS_ONLINE)
        pictureName = ":/images/serverONLINE.png";
    else if(_status == NetStatus::NET_STATUS_OFFLINE)
        pictureName = ":/images/serverOFFLINE.png";
    else if(_status == NetStatus::NET_STATUS_INVALID)
        pictureName = ":/images/serverUNKNOWN.png";

    QImage img(pictureName);

    this->setPos(0, 0);
    this->setPixmap(QPixmap::fromImage(img));

}

void SphereServerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*
    //QGraphicsRectItem::paint(painter, option);

    QPen pen;
    pen.setColor(Qt::black);

    //QRectF rec = option->exposedRect;

    qDebug() << "rec.x = " << _rec.x() << "rec.y = " << _rec.y();

    painter->setPen(pen);

    QString pictureName = "";

    if(_status == NetStatus::NET_STATUS_ONLINE)
        pictureName = ":/images/serverONLINE.png";
    else if(_status == NetStatus::NET_STATUS_OFFLINE)
        pictureName = ":/images/serverOFFLINE.png";
    else if(_status == NetStatus::NET_STATUS_INVALID)
        pictureName = ":/images/serverUNKNOWN.png";

    QImage img(pictureName);
    //img.scaled(_rec.width(), _rec.height());

    painter->drawImage(_rec.x() + 10, _rec.y() + 20, img);
    painter->drawText(QRectF(_rec.x() + 10, _rec.y() + 10, _rec.height(), _rec.width()), _name);

    //this->setPixmap(QPixmap::fromImage(img));
    //this->setPos(0, 0);

*/


}

// SphereManagerItem --------------------------------

SphereManagerItem::SphereManagerItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      _name(name),
      _status(status),
      _rec(rect)
{

}

void SphereManagerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsRectItem::paint(painter, option);

    QPen pen;
    pen.setColor(Qt::black);

    //QRectF rec = option->exposedRect;

    qDebug() << "rec.x = " << _rec.x() << "rec.y = " << _rec.y();

    QImage img(":/images/managerONLINE.png");
    img.scaled(_rec.width(), _rec.height());

    painter->setPen(pen);
    painter->drawText(QRectF(_rec.x() + 10, _rec.y() + 10, _rec.height(), _rec.width()), _name);
    painter->drawImage(_rec.x() + 10, _rec.y() + 20, img);


}

// SphereArmItem --------------------------------

SphereArmItem::SphereArmItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      _name(name),
      _status(status),
      _rec(rect)
{

}

void SphereArmItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsRectItem::paint(painter, option);

    QPen pen;
    pen.setColor(Qt::black);

    //QRectF rec = option->exposedRect;

    qDebug() << "rec.x = " << _rec.x() << "rec.y = " << _rec.y();

    painter->setPen(pen);
    painter->drawText(QRectF(_rec.x() + 10, _rec.y() + 10, _rec.height(), _rec.width()), _name);
    painter->drawImage(_rec.x() + 10, _rec.y() + 20, QImage(":/images/armONLINE.png"));


}

// SpherePausItem --------------------------------

SpherePausItem::SpherePausItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      _name(name),
      _status(status),
      _rec(rect)
{

}

void SpherePausItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsRectItem::paint(painter, option);

    QPen pen;
    pen.setColor(Qt::black);

    //QRectF rec = option->exposedRect;

    qDebug() << "rec.x = " << _rec.x() << "rec.y = " << _rec.y();

    painter->setPen(pen);
    painter->drawText(QRectF(_rec.x() + 10, _rec.y() + 10, _rec.height(), _rec.width()), _name);
    painter->drawImage(_rec.x() + 10, _rec.y() + 20, QImage(":/images/pausONLINE.png"));


}

