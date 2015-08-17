#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _sphereView = new SphereWiew();

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(_sphereView);


    QWidget* centralWgt = new QWidget;
    centralWgt->setLayout(layout);

    setCentralWidget(centralWgt);

    _sphereView->addItem("Server1", true);
    _sphereView->addItem("Server2", true);
    _sphereView->addItem("Server3", false);
    _sphereView->addItem("Server4", true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
