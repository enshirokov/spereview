#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _sphereView = new TopologyViewer();

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(_sphereView);


    QWidget* centralWgt = new QWidget;
    centralWgt->setLayout(layout);

    setCentralWidget(centralWgt);

    QString str = "Manager;2;0\nServer1;3;1\nServer2;3;0\nServer3;3;1\nServer4;3;1\nArm;0;1\nPaus;1;1\n";
    _sphereView->setData(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}
