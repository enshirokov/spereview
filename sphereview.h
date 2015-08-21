#ifndef SPHEREVIEW_H
#define SPHEREVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>

const int ITEM_SIZE = 100;

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

class SphereView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SphereView(QWidget *parent = 0);
    ~SphereView();

    void setData(QString data);

private:
    void resizeEvent (QResizeEvent* event);
    void wheelEvent(QWheelEvent*);

    void addServerItem(const QString &name, NetStatus status);
    void addManagerItem(const QString &name, NetStatus status);
    void addArmItem(const QString &name, NetStatus status);
    void addPausItem(const QString &name, NetStatus status);

signals:

public slots:

private:
    QGraphicsScene* _scene;
    QGraphicsItemGroup* _group;

    double x0;
    double y0;
    double x1;
    double y1;
    double x2;
    double y2;
};


class SphereServerItem : public QGraphicsPixmapItem
{
    //Q_OBJECT
public:
    explicit SphereServerItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    //void mouseMoveEvent();


private:
    QString _name;
    NetStatus _status;

    QRectF _rec;
};

class SphereManagerItem : public QGraphicsPixmapItem
{
    //Q_OBJECT
public:
    explicit SphereManagerItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    //void mouseMoveEvent();

private:
    QString _name;
    NetStatus _status;

    QRectF _rec;
};

class SphereArmItem : public QGraphicsPixmapItem
{
    //Q_OBJECT
public:
    explicit SphereArmItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    //void mouseMoveEvent();

private:
    QString _name;
    NetStatus _status;

    QRectF _rec;
};

class SpherePausItem : public QGraphicsPixmapItem
{
    //Q_OBJECT
public:
    explicit SpherePausItem(const QString &name, const QRectF &rect, NetStatus status, QGraphicsItem *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    //void mouseMoveEvent();

private:
    QString _name;
    NetStatus _status;

    QRectF _rec;
};

#endif // SPHEREWIEW_H
