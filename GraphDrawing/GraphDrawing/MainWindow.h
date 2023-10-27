#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Graph.h"
#include <QMouseEvent>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QObject>
#include <QCoreApplication>
#include <math.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    void CreatRadioButton();
private slots:
    void selectUndirected();
    void selectDirected();
private:
    Ui::MainWindowClass ui;
    Graph graph;
    Node firstNode;
    QRadioButton* buttonUndirected;
    QRadioButton* buttonDirected;
    QVBoxLayout* layout;
    bool paintEnable;
};
