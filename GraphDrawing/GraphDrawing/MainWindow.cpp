#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    layout = new QVBoxLayout();
    buttonDirected = new QRadioButton("Directed Graph");
    buttonUndirected = new QRadioButton("Undirected Graph");
    graph.setType(-1);
    connect(buttonDirected, &QRadioButton::clicked, this, &MainWindow::selectDirected);
    connect(buttonUndirected, &QRadioButton::clicked, this, &MainWindow::selectUndirected);
}

MainWindow::~MainWindow()
{}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (graph.getType()!=-1)
    {
        if (event->button() == Qt::RightButton)
        {
            QRect buttonDirectedPos = buttonDirected->geometry();
            QRect buttonUndirectedPos = buttonUndirected->geometry();
            QRect clickRect(event->pos(), QSize(20, 20));
            if (!(buttonDirectedPos.intersects(clickRect) || buttonUndirectedPos.intersects(clickRect)))
            {
                graph.AddNode(event->pos());
                update();
            }
        }
        else if (event->button() == Qt::LeftButton)
        {
            std::vector<Node> nodes = graph.getNodes();
            for (Node& node : nodes)
            {
                if (fabs(node.getPosition().x() - event->pos().x()) < 20 &&
                    fabs(node.getPosition().y() - event->pos().y()) < 20)
                {
                    if (firstNode.getValue() == -1)
                    {
                        firstNode = node;
                        update();
                    }
                    else
                    {
                        graph.AddArch(firstNode, node);
                        firstNode.setValue(-1);
                        update();
                    }
                    break;
                }
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    if (graph.getType() != -1)
    {
        QPainter paint(this);
        std::vector<Node> nodes = graph.getNodes();
        for (Node& node : nodes)
        {
            QRect rectangle(node.getPosition().x() - 10, node.getPosition().y() - 10, 20, 20);
            QString string;
            string.setNum(node.getValue());
            if (firstNode == node)
            {
                paint.setPen(Qt::black);
                paint.setBrush(Qt::green);
            }
            else
            {
                paint.setPen(Qt::black);
                paint.setBrush(Qt::white);
            }
            paint.drawEllipse(rectangle);
            paint.drawText(rectangle, Qt::AlignCenter, string);
        }
        std::vector<Arch> arches = graph.getAches();
        for (Arch& arch : arches)
        {
            int radius = 10;
            QPoint startP(arch.getFirstNode().getPosition().x(), arch.getFirstNode().getPosition().y());
            QPoint endP(arch.getSecondNode().getPosition().x(), arch.getSecondNode().getPosition().y());
            double angle = std::atan2(endP.y() - startP.y(), endP.x() - startP.x());
            startP.setX(startP.x() + radius * cos(angle));
            startP.setY(startP.y() + radius * sin(angle));
            endP.setX(endP.x() - radius * cos(angle));
            endP.setY(endP.y() - radius * sin(angle));
            paint.drawLine(startP, endP);
            if (graph.getType() == 1)
            {
                int sizeArrow = 10;
                paint.drawLine(endP.x(), endP.y(), endP.x() - sizeArrow * std::cos(angle - M_PI / 6), endP.y() - sizeArrow * std::sin(angle - M_PI / 6));
                paint.drawLine(endP.x(), endP.y(), endP.x() - sizeArrow * std::cos(angle + M_PI / 6), endP.y() - sizeArrow * std::sin(angle + M_PI / 6));
            }
        }
    }
}

void MainWindow::selectDirected()
{
    graph.setType(1);
    buttonUndirected->setDisabled(true);
}

void MainWindow::selectUndirected()
{
    graph.setType(2);
    buttonDirected->setDisabled(true);
}

void MainWindow::CreatRadioButton()
{
    layout->addWidget(buttonDirected);
    layout->addWidget(buttonUndirected);
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}



