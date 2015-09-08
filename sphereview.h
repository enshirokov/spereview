#ifndef SPHEREVIEW_H
#define SPHEREVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>



enum SphereHostType
{
    HOST_TYPE_ARM,
    HOST_TYPE_PAUS,
    HOST_TYPE_MANAGER,
    HOST_TYPE_SERVER,
    HOST_TYPE_INVALID
};

enum NetStatus
{
    NET_STATUS_ONLINE,
    NET_STATUS_OFFLINE,
    NET_STATUS_INVALID
};

class SphereItem;

class TopologyViewer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TopologyViewer(QWidget *parent = 0);
    ~TopologyViewer();

    void setData(QString data);

private:
    void resizeEvent (QResizeEvent* event);
    void wheelEvent(QWheelEvent*);


    void addManagerItem(const QString &name, NetStatus status, QGraphicsItemGroup *group);
    void addServerItem(const QString &name, NetStatus status, QGraphicsItemGroup *group);
    void addArmItem(const QString &name, NetStatus status, QGraphicsItemGroup *group);
    void addPausItem(const QString &name, NetStatus status, QGraphicsItemGroup *group);

    QGraphicsPathItem* drawConnection(const QPointF &from, const QPointF &to);
    void createConnection(QGraphicsItemGroup *group, QGraphicsItemGroup *item);

signals:

public slots:

private:
    qreal scaleFactor;

    QGraphicsScene* _scene;
    QGraphicsItemGroup* _groupCenter;
    QGraphicsItemGroup* _groupRight;
    QGraphicsItemGroup* _groupLeft;

    double xLeft; // left gtoup
    double yLeft;
    double xCenter; // central group
    double yCenter;
    double xRight; // right group
    double yRight;
};

class SphereItem : public QGraphicsItem
{
    //Q_OBJECT
public:
    explicit SphereItem(const QString &name, const QRectF &rect, const QString &img, QGraphicsItem *parent = 0);

    QPointF connectPointLeft();
    QPointF connectPointRight();
    QPointF center();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;



private:
    QString _name;
    QString _img;
    QRectF _rec;
};


#endif // SPHEREWIEW_H
