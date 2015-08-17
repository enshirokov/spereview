#ifndef SPHEREWIEW_H
#define SPHEREWIEW_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

const int ITEM_SIZE = 100;

class SphereWiew : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SphereWiew(QWidget *parent = 0);
    ~SphereWiew();

    void addItem(QString name, bool status);

signals:

public slots:

private:
    QGraphicsScene* _scene;
    QGraphicsItemGroup* _group;

    double x;
    double y;
};


class SphereItem : public QGraphicsRectItem
{
    //Q_OBJECT
public:
    explicit SphereItem(const QString &name, const QRectF &rect, QGraphicsItem *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    //void mouseMoveEvent();

private:
    QString _name;
};

#endif // SPHEREWIEW_H
