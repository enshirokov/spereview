#include "sphereview.h"
#include <QGraphicsRectItem>
#include <qDebug>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

const int ITEM_SIZE = 100;
const int SCENE_SIZE_X = 500;
const int SCENE_SIZE_Y = 500;
const int OFFSET = 40;
const double SCALE_LIMIT = 1;
const double SCALE_FACTOR = 0.2;

TopologyViewer::TopologyViewer(QWidget *parent)
    : QGraphicsView(parent),
      scaleFactor(SCALE_LIMIT)
{
    xLeft = 0;
    yLeft = 0;

    xCenter = SCENE_SIZE_X/2;
    yCenter = SCENE_SIZE_Y/2;

    xRight = SCENE_SIZE_X;
    yRight = 0;


    _scene = new QGraphicsScene;
    this->setScene(_scene);

    //this->setResizeAnchor(QGraphicsView::NoAnchor);
    //this->setAlignment(Qt::AlignCenter);

    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _groupLeft = _scene->createItemGroup(QList<QGraphicsItem*>());
    _groupLeft->setX(xLeft);
    _groupLeft->setY(yLeft);
    _groupCenter = _scene->createItemGroup(QList<QGraphicsItem*>());
    _groupCenter->setX(xCenter);
    _groupCenter->setY(yCenter);
    _groupRight = _scene->createItemGroup(QList<QGraphicsItem*>());
    _groupRight->setX(xRight);
    _groupRight->setY(yRight);

    setBackgroundBrush(QBrush(QColor(80, 80, 80), Qt::SolidPattern));

    setRenderHints(QPainter::Antialiasing); // item smoothing
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    setDragMode(ScrollHandDrag);
    //setInteractive(false);

}

TopologyViewer::~TopologyViewer()
{
    _scene->destroyItemGroup(_groupLeft);
    _scene->destroyItemGroup(_groupCenter);
    _scene->destroyItemGroup(_groupRight);
}

void TopologyViewer::resizeEvent (QResizeEvent* event)
{
    setSceneRect(_scene->itemsBoundingRect());
}

void TopologyViewer::wheelEvent(QWheelEvent * event)
{

    int angle = event->delta();

    if(angle > 0){

        scaleFactor += SCALE_FACTOR;
        this->scale(1.2, 1.2);

    }
    else{
        if(scaleFactor > SCALE_LIMIT){
            scaleFactor -= SCALE_FACTOR;
            this->scale(1/1.2, 1/1.2);
        }

    }

}


void TopologyViewer::setData(QString data)
{
    QStringList list = data.split("\n");


    for(auto x: list){

        if(x.size() < 1)
            continue;

        QStringList unit = x.split(";");

        switch(unit.at(1).toInt()){
        case SphereHostType::HOST_TYPE_ARM:
            addArmItem(unit.at(0), (NetStatus)unit.at(2).toInt(), _groupLeft);
            break;
        case SphereHostType::HOST_TYPE_PAUS:
            addPausItem(unit.at(0), (NetStatus)unit.at(2).toInt(), _groupLeft);
            break;
        case SphereHostType::HOST_TYPE_MANAGER:
            addManagerItem(unit.at(0), (NetStatus)unit.at(2).toInt(), _groupCenter);
            break;
        case SphereHostType::HOST_TYPE_SERVER:
            addServerItem(unit.at(0), (NetStatus)unit.at(2).toInt(), _groupRight);
            break;


        default:
            qDebug() << "Unknown type!";
        }
    }


    createConnection(_groupLeft, _groupCenter);
    createConnection(_groupRight, _groupCenter);



    qDebug() << _scene->itemsBoundingRect();

}

QGraphicsPathItem* TopologyViewer::drawConnection(const QPointF &from, const QPointF &to)
{
/*
    if(from.x() > to.x())
        return nullptr;
*/

    int mX = /*abs*/((to.x() - from.x())/2); // середина отрезка между точками p0 и p1 по оси x
    int mY = /*abs*/((to.y() - from.y())/2); // середина отрезка между точками p0 и p1 по оси y

    QPoint p0 = QPoint(from.x() + mX, from.y() + mY); // центр

    QPainterPath path;

    path.moveTo(from);

    path.cubicTo(QPoint(p0.x(), from.y()), QPoint(p0.x(), to.y()), to);

    return new QGraphicsPathItem(path);
}

void TopologyViewer::createConnection(QGraphicsItemGroup *group, QGraphicsItemGroup *groupCenter)
{
    if(groupCenter->childItems().empty()){
        // сообщить об ошибке
        return;
    }

    SphereItem* nodeCentral = (SphereItem*)groupCenter->childItems().at(0);

    for(auto x : group->childItems()){

        SphereItem* node = (SphereItem*)x;

        QPointF pointFrom = node->center();
        QPointF pointTo = nodeCentral->center();

        QGraphicsPathItem* p = nullptr;

        if(pointFrom.x() < pointTo.x())
            p = drawConnection(node->connectPointRight(), nodeCentral->connectPointLeft());
        else
            p = drawConnection(nodeCentral->connectPointRight(), node->connectPointLeft());


        if(p != nullptr){

            QPen pen;
            pen.setWidth(2);
            pen.setColor(QColor(0, 180, 180));
            pen.setCosmetic(true);
            p->setPen(pen);

            group->addToGroup(p);
        }
    }
}

void TopologyViewer::addServerItem(const QString &name, NetStatus status, QGraphicsItemGroup *group)
{

    QString pictureName = "";

    if (status == NetStatus::NET_STATUS_ONLINE)
        pictureName = ":/images/sphere_server_online_48.png";
    else if (status == NetStatus::NET_STATUS_OFFLINE)
        pictureName = ":/images/sphere_server_offline_48.png";
    else if (status == NetStatus::NET_STATUS_INVALID)
        pictureName = ":/images/sphere_server_unk_48.png.png";


    SphereItem* item = new SphereItem(name, QRectF(xRight, yRight, ITEM_SIZE, ITEM_SIZE), pictureName);
    group->addToGroup(item);

    yRight += ITEM_SIZE + OFFSET;

}

void TopologyViewer::addManagerItem(const QString &name, NetStatus status, QGraphicsItemGroup *group)
{
    QString pictureName = "";

    if (status == NetStatus::NET_STATUS_ONLINE)
        pictureName = ":/images/sphere_manager_offline_48.png";
    else if (status == NetStatus::NET_STATUS_OFFLINE)
        pictureName = ":/images/sphere_manager_online_48.png";
    else if (status == NetStatus::NET_STATUS_INVALID)
        pictureName = ":/images/sphere_manager_unk_48.png";

    SphereItem* item = new SphereItem(name, QRectF(xCenter, yCenter, ITEM_SIZE, ITEM_SIZE), pictureName);
    group->addToGroup(item);

    yCenter += ITEM_SIZE + OFFSET;

}

void TopologyViewer::addArmItem(const QString &name, NetStatus status, QGraphicsItemGroup *group)
{
    QString pictureName = "";

    if (status == NetStatus::NET_STATUS_ONLINE)
        pictureName = ":/images/sphere_arm_online_48.png";
    else if (status == NetStatus::NET_STATUS_OFFLINE)
        pictureName = ":/images/sphere_arm_offline_48.png";
    else if (status == NetStatus::NET_STATUS_INVALID)
        pictureName = ":/images/sphere_arm_unk_48.png";

   SphereItem* item = new SphereItem(name, QRectF(xLeft, yLeft, ITEM_SIZE, ITEM_SIZE), pictureName);
   group->addToGroup(item);

   yLeft += ITEM_SIZE + OFFSET;

}

void TopologyViewer::addPausItem(const QString &name, NetStatus status, QGraphicsItemGroup *group)
{
    QString pictureName = "";

    if (status == NetStatus::NET_STATUS_ONLINE)
        pictureName = ":/images/sphere_paus_online_48.png";
    else if (status == NetStatus::NET_STATUS_OFFLINE)
        pictureName = ":/images/sphere_paus_offline_48.png";
    else if (status == NetStatus::NET_STATUS_INVALID)
        pictureName = ":/images/sphere_paus_unk_48.png";

    SphereItem* item = new SphereItem(name, QRectF(xLeft, yLeft, ITEM_SIZE, ITEM_SIZE), pictureName);
    group->addToGroup(item);

    yLeft += ITEM_SIZE + OFFSET;

}

// SphereItem --------------------------------

SphereItem::SphereItem(const QString &name, const QRectF &rect, const QString &img, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      _name(name),
      _rec(rect),
      _img(img)
{


    //setPos(_rec.x(), _rec.y());
}

void SphereItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(Qt::black);

    painter->setPen(pen);

    painter->drawImage(_rec, QImage(_img));
    painter->drawText(QRectF(_rec.x(), _rec.y() + _rec.width(), _rec.width(), _rec.height()), _name);

}


QRectF SphereItem::boundingRect() const
{
    QPointF realX = /*mapToScene*/(QPoint(_rec.x(), _rec.y()));
    QPointF realY = /*mapToScene*/(QPoint(_rec.width(), _rec.height()));

    QRectF recTmp  = QRectF(realX.x(), realX.y(), realY.x(), realY.y());

    return recTmp;
}


QPainterPath SphereItem::shape() const
{
    QRectF rect = boundingRect();
    QPainterPath path;
    path.addRoundedRect(rect,0,0);
    return path;
}

QPointF SphereItem::connectPointRight()
{
    QPointF point = mapToScene(QPointF(_rec.x() + _rec.width(), (_rec.y() + _rec.height()/2)));

    return point;
}

QPointF SphereItem::connectPointLeft()
{
    QPointF point = mapToScene(QPointF(_rec.x(), (_rec.y() +_rec.height()/2)));

    return point;
}

QPointF SphereItem::center()
{
    QPointF point = mapToScene(QPointF((_rec.x() + _rec.width()/2), (_rec.y() + _rec.height()/2)));

    return point;
}


