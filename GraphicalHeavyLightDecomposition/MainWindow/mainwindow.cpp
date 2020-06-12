#include "mainwindow.h"

MainWindow::MainWindow(const QString & windowName,int titleBarHeight) : windowName(windowName),titleBarHeight(titleBarHeight),treeReader (TreeReader(this))
  ,treeView(new QGraphicsView())
{
    init();
    showMaximized();
    //qInfo() << "end of coordinates calculation";
    /*auto centralWidget = new QWidget();
    centralWidget->setLayout(gridLayout);
    setWindowTitle(windowName);
    setCentralWidget(centralWidget);

    //gridLayout->addWidget(DummyWidget::getDummyWidget(),0,0);
    //nodes
    QPixmap pixmap(51,51);
    pixmap.fill(Qt::transparent);
    auto painter = QPainter(&pixmap);
    painter.setBrush(QBrush(Qt::yellow));
    painter.drawEllipse(0,0,50,50);
    painter.end();
    QLabel * node = new QLabel();
    QLabel * node2 = new QLabel();
    QLabel * node3 = new QLabel();
    QLabel * node4 = new QLabel();
    QLabel * node5 = new QLabel();
    node->setPixmap(pixmap);
    node2->setPixmap(pixmap);
    node3->setPixmap(pixmap);
    node4->setPixmap(pixmap);
    node5->setPixmap(pixmap);
    gridLayout->addWidget(node,0,5);
    gridLayout->addWidget(node2,2,3);
    gridLayout->addWidget(node3,2,7);
    gridLayout->addWidget(node4,4,2);
    gridLayout->addWidget(node5,4,5);
    //edges
    QPixmap pixmap2(51,51);
    pixmap2.fill(Qt::transparent);
    auto painter2 = QPainter(&pixmap2);
    painter2.setBrush(QBrush(Qt::black));
    painter2.drawLine(50,0,0,50);
    painter2.drawText(8,20,"32");
    painter2.end();
    QPixmap pixmap3(51,51);
    pixmap3.fill(Qt::transparent);
    auto painter3 = QPainter(&pixmap3);
    painter3.setBrush(QBrush(Qt::black));
    painter3.drawLine(0,0,50,50);
    painter3.drawText(30,25,"15");
    painter3.end();
    QLabel * edge = new QLabel();
    QLabel * edge2 = new QLabel();
    edge->setPixmap(pixmap2);
    gridLayout->addWidget(edge,1,4);
    edge2->setPixmap(pixmap3);
    gridLayout->addWidget(edge2,1,6);*/
}

void MainWindow::init(){
    auto coordinates=treeReader.getNodeCoordinates(width(),height());
    for(auto coordinate : coordinates)
        qInfo() << coordinate.first << " " << coordinate.second ;
    auto graph = treeReader.getGraph();
    auto canvas = new Canvas(coordinates,graph,titleBarHeight,width(),height());
    treeView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    treeView->setScene(canvas);
    auto mainLayout = new QVBoxLayout();
    auto centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(treeView);
    qInfo() << "filePath from mainWindow.cpp: " << treeReader.getPath() ;
    mainLayout->addWidget(new Controls(graph.size(),treeReader.getPath(),canvas));
    setCentralWidget(centralWidget);
}
