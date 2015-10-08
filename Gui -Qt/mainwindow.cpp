#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDesktopWidget>
#include <QString>
#include <QRect>
#include <QHeaderView>
#include <QFont>
#include <QLabel>
#include <QImageReader>
#include <QImage>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    sizeTable=10;
    QFile qss(":/stylesheets/default.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();
    Paint();
}

void MainWindow::Paint()
{
    this->resize(600,600);
    initBoard();
    move = new QPushButton("Move",this);
    move->setFont(QFont("red"));
    move->setGeometry(QRect(50,480,80,40));
    move->setEnabled(true);
    connect(move, SIGNAL (released()), this, SLOT (handleButtonMove()));
    for(int i=0;i<sizeTable;++i)
    {
        for(int j=0;j<sizeTable;++j)
        {
            if(i<=3 && ((i+j)%2==1))
                drawPiece(i,j,"white");
            else if(i>5 && ((i+j)%2==1))
                drawPiece(i,j,"black");
        }
    }
}

void MainWindow::initBoard()
{
    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(sizeTable);
    tableWidget->setColumnCount(sizeTable);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    tableWidget->horizontalHeader()->sectionResizeMode(QHeaderView::Fixed);
    tableWidget->verticalHeader()->setDefaultSectionSize(40);
    tableWidget->horizontalHeader()->setDefaultSectionSize(40);
    tableWidget->setFixedSize(406,406);
    tableWidget->setGeometry(QRect(50,50,50+40*sizeTable,50+40*sizeTable));
    for(int i=0;i<sizeTable;++i)
    {
        for(int j=0;j<sizeTable;++j)
        {
            if((i+j)%2==1)
            {
                QTableWidgetItem* color = new QTableWidgetItem();
                color->setBackground(QBrush(QColor(162,117,27)));
                tableWidget->setItem(i,j,color);
            }
            else
            {
                QTableWidgetItem* color = new QTableWidgetItem();
                color->setBackground(QBrush(QColor(187,199,17)));
                tableWidget->setItem(i,j,color);
            }
        }
    }
}

void MainWindow::handleButtonMove()
{
    int x=rand()%10;
    int y=rand()%10;
    clearCell(x,y);
}

void MainWindow::drawPiece(int x,int y,std::string color)
{
    QPixmap pix=QPixmap(QString::fromStdString(":/images/"+color+".png"));
    QPixmap resPix = pix.scaled(30,30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QLabel *label =new QLabel();
    label->setPixmap(resPix);
    label->setAlignment(Qt::AlignCenter);
    tableWidget->setCellWidget(x,y,label);
}

void MainWindow::clearCell(int x,int y)
{
    QLabel *label=new QLabel("");
    tableWidget->setCellWidget(x,y,label);
}


MainWindow::~MainWindow()
{
}

void MainWindow::UpdateTable(int x,int y)
{
    QTableWidgetItem* green = new QTableWidgetItem();
    green->setBackground(QBrush(QColor(Qt::blue)));
    tableWidget->setItem(x,y,green);
}
