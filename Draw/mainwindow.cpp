#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Parser.h"

#define Recwedith 80
#define Recheight 40
#define Rediuos 15




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
    Parser p1;
    p1.read_file("Example.txt");
    Node* Output = p1.statement_seq();
//    DrawCircle(QPoint(150,150) , 30 , Qt::red  , "id(x)");

   DrawTree(Output,20,20);
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


int MainWindow:: DrawTree(Node* root,int x,int y ){

    QString qstr = QString::fromStdString(root->value);
    DrawRec(x,y,Recwedith,Recheight,Qt::red ,qstr);

    int x_move = 0 ;

    int max_children=0;
    int node_children;

    y += 70;

    for(list<Node *>::iterator it=root->children.begin(); it != root->children.end(); it++){
       node_children =  DrawTree(*it, x+x_move, y );
       if (max_children<node_children) max_children = node_children;
       x_move += 90 + (max_children-1) *90 ;

    }

    return root->children.size();

}




