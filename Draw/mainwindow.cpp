#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: paintEvent(QPaintEvent *event)
{
    DrawCircle(QPoint(150,150) , 30 , Qt::red  , "id(x)");
}
void MainWindow:: DrawRec(int x , int y , int w , int h , Qt::GlobalColor color  , QString text){
    QPainter painter(this);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);

    painter.setPen(pen);

    QRect rec1(x,y,w,h);
    QPoint r1_c = rec1.center();

    QFont font1("Volkhov",13,QFont::Light,true);
    painter.setFont(font1);
    QFontMetrics fm(font1);

    int wfont = fm.width(text);
    r1_c = r1_c - QPoint(wfont/2 , 0);

    painter.setPen(pen);
    painter.drawText(r1_c,  text);
    painter.drawRect(rec1);
}

void MainWindow:: DrawCircle(QPoint c , int r , Qt::GlobalColor color  , QString text){
    QPainter painter(this);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);

    painter.setPen(pen);

    QFont font1("Volkhov",13,QFont::Light,true);
    painter.setFont(font1);
    QFontMetrics fm(font1);

    int wfont = fm.width(text);
    QPoint Ctext = c - QPoint(wfont/2 , 0);

    painter.setPen(pen);
    painter.drawText(Ctext,  text);
    painter.drawEllipse(c,r,r);
}
