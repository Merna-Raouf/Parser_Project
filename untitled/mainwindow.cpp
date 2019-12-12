#include "mainwindow.h"
#include "ui_mainwindow.h"


#define RECT_H 80   // rectangle height
#define RECT_W 100 // rectangle width
#define Cir_R 35

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->removeToolBar(ui->mainToolBar);
    this->statusBar()->setVisible(false);
    mainPalette = new QPalette;
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);

    this->setWindowTitle("Recursive Descent Parser");
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::InitUI()
{
    directory = new string () ;
    QFont font2("Volkhov",11,QFont::Light,true);

    //Input file button -> browse
    browse = new QPushButton();
    browse->setText("Browse File");
    browse->setMinimumHeight(35);
    browse->setFont(font2);


    //Simulate button
    Simulate = new QPushButton();
    Simulate->setText("Simulate");
    Simulate->setMinimumHeight(35);
    Simulate->setFont(font2);

    //page title
    firstPagetitle = new QLabel("Recursive Descent Parser");
    QFont font("Volkhov",15,QFont::Bold,true);
    firstPagetitle->setFont(font);

    //adding to form layout
    firstInputPage = new QFormLayout;
    firstInputPage->setContentsMargins(10,10,10,10);
    firstInputPage->setSpacing(20);
    firstInputPage->addRow(firstPagetitle);


    firstInputPage->addRow(browse);
    firstInputPage->addRow(Simulate);

    mainLayout = new QHBoxLayout;
    mainLayout->addItem(firstInputPage);


    //adding main layout to central widget of window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    //making signals for buttons
    QObject::connect(browse,SIGNAL(clicked()),this,SLOT(browsefun()));
    QObject::connect(Simulate,SIGNAL(clicked()),this,SLOT(DrawTree()));

}
void MainWindow :: browsefun(){
    QString filename = QFileDialog::getOpenFileName(this,
                                                 tr("Open File"),
                                                 "H:\Nader 2014\CSE_2ndYear\Compilers\Project\src",
                                                    "Text files (*.txt)");

    *directory = filename.toStdString();
}
void MainWindow:: DrawTree(){

    if(*directory == ""){
        QMessageBox::warning(this,"Input File Error","Please Select an input file");
        return;
    }

    s1 = new SubWindow(this,*directory);
    s1->setModal(true);
    s1->setWindowTitle("Syntax Tree");
    s1->setFixedSize(QSize(1050,600));
    s1->exec();
}
/*
// ////////////////////////////////////////////////////////////////
void MainWindow:: paintEvent(QPaintEvent *event)
{

    Parser p1;
    p1.read_file("C:\\Users\\Nader\\Documents\\untitled\\Example.txt");
    Node* Output = p1.statement_seq();

    DrawTree(Output,50,10,QRect(10,10,10,10),"None");

    QRect rec1 = DrawRec(350 , 80 , "ASSIGN");
    QRect rec2 = DrawRec(350 , rec1.center().y() + (20+RECT_H) , "ASSIGN");
    QRect rec3 = DrawRec(350, rec2.center().y() + (20+RECT_H) , "ASSIGN");
    QRect rec4 = DrawRec(rec3.center().x() + RECT_W , rec3.center().y() - RECT_H/2 , "ASSIGN");

    connectRectoChildRec(rec1,rec2);
    connectRectoChildRec(rec2,rec3);
    connectSiblingRects(rec3,rec4);

    QRect Ellipse1 = DrawCircle(rec4.center()+QPoint(0,(20+RECT_H)),"Op\n(-)");
    connectRectoChildCir(rec4,Ellipse1);

    QRect Ellipse2 = DrawCircle(Ellipse1.center()+QPoint(0,2*RECT_H),"Op\n(-)");

    QRect Ellipse3 = DrawCircle(Ellipse1.center()+QPoint(Cir_R*4,2*RECT_H),"Op\n(-)");

    connectCirtoChildCir(Ellipse1,Ellipse2);
    connectCirtoChildCir(Ellipse1,Ellipse3);

    QRect Ellipse4 = DrawCircle(Ellipse3.center()+QPoint(0,2*RECT_H),"Op\n(-)");
    QRect Ellipse5 = DrawCircle(Ellipse3.center()+QPoint(Cir_R*4,2*RECT_H),"Op\n(-)");

    connectCirtoChildCir(Ellipse3,Ellipse4);
    connectCirtoChildCir(Ellipse3,Ellipse5);

}
int MainWindow:: DrawTree(Node* root,int x,int y , QRect prev , string prev_type ){

    QString text = QString::fromStdString(root->value);

    if(root->drawn==false &&
            (root->value == "if" || root->value == "Repeat"
             || root->value == "Assign" || root->value == "read"
             || root->value == "write"  || root->value == "StatementSeq")){

        if (root->value == "StatementSeq"){
            root->drawn = true;
            root->children.front()->drawn = true;

            text = QString::fromStdString(root->children.front()->value);

            if(root->children.front()->value == "Assign" || root->children.front()->value == "read"){
                text = QString::fromStdString(root->children.front()->value) + "("
                        + QString::fromStdString(root->children.front()->children.front()->value) + ")";

                root->children.front()->children.front()->drawn = true;
            }

        }
        else if(root->value == "Assign" || root->value == "read"){
            text = QString::fromStdString(root->value) + "("
                    + QString::fromStdString(root->children.front()->value) + ")";
            root->drawn = true;
            root->children.front()->drawn = true;
        }
        QRect newRec = DrawRec(x,y,text);
        y = newRec.center().y() + (20+RECT_H);

        if(prev_type == "Rect"){
            connectRectoChildRec(prev,newRec);
        }
        prev_type = "Rect";
        prev = newRec;
    }
    else if (root->drawn==false){
       if(root->type == "IDENTIFIER")
           text = "id(" +  QString::fromStdString(root->value) + ")";

       else if (root->type == "NUMBER")
           text = "const("  + QString::fromStdString(root->value) + ")";

       QRect newElipse = DrawCircle(QPoint(x,y),text);
       y = newElipse.center().y()+2*RECT_H;

       if(prev_type == "Rect"){
           connectRectoChildCir(prev,newElipse);
       }
       else if (prev_type == "Cir"){
           connectCirtoChildCir(prev,newElipse);
       }
       prev_type = "Cir";
       prev = newElipse;
    }

    int x_move = 0 ;
    int max_children=0;
    int node_children;


    for(list<Node *>::iterator it=root->children.begin(); it != root->children.end(); it++){
       node_children =  DrawTree(*it, x+x_move, y , prev , prev_type);
       if (max_children<node_children) max_children = node_children;
       x_move += 90 + (max_children) *90 ;
    }

    return root->children.size();

}

QRect MainWindow:: DrawRec(int x , int y , QString text){
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);

    painter.setPen(pen);

    QRect rec1(x,y,RECT_W,RECT_H);
    QPoint r1_c = rec1.center();

    QFont font1("Volkhov",13,QFont::Light,true);
    painter.setFont(font1);
    QFontMetrics fm(font1);

    int wfont = fm.width(text);
    r1_c = r1_c - QPoint(wfont/2 , 0);

    painter.drawText(r1_c,  text);

    pen.setColor(Qt::red);
    painter.setPen(pen);

    painter.drawRect(rec1);

    return rec1;
}

QRect MainWindow:: DrawCircle(QPoint c , QString text){
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);

    painter.setPen(pen);

    QFont font1("Volkhov",13,QFont::Light,true);
    painter.setFont(font1);
    QFontMetrics fm(font1);

    int wfont = fm.width(text);
    QPoint Ctext = c - QPoint(wfont/2 , 0);

    QRect Ellipse (c.x() - Cir_R, c.y() - Cir_R, 2 * Cir_R, 2 * Cir_R);

    painter.drawText(Ctext,  text);

    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawEllipse(Ellipse);

    return Ellipse;
}

void MainWindow :: connectRectoChildRec(QRect rec1 , QRect rec2){
    QPoint start = rec1.center() + QPoint(0,RECT_H/2);
    QPoint end = rec2.center() - QPoint(0,RECT_H/2);

    matchingLine(start , end ,Qt::blue);
}
void MainWindow :: connectRectoChildCir(QRect rec1 , QRect Ellipse){
    QPoint start = rec1.center() + QPoint(0,RECT_H/2);
    QPoint end = Ellipse.center() - QPoint(0,Cir_R);

    matchingLine(start , end ,Qt::blue);
}

void MainWindow :: connectCirtoChildCir(QRect Ellipse1 , QRect Ellipse2){
    QPoint start = Ellipse1.center() + QPoint(0,Cir_R);
    QPoint end = Ellipse2.center() - QPoint(0,Cir_R);

    matchingLine(start , end ,Qt::blue);
}

void MainWindow :: connectSiblingRects(QRect rec1 , QRect rec2){
    QPoint start = rec1.center() + QPoint(RECT_W/2,0);
    QPoint end = rec2.center() - QPoint(RECT_W/2,0);

    matchingLine(start , end ,Qt::blue);
}
void MainWindow :: matchingLine(QPoint start , QPoint end , Qt::GlobalColor color){
    QPainter painter(this);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);

    painter.setPen(pen);

    QFont font1("Volkhov",13,QFont::Light,true);
    painter.setFont(font1);
    QFontMetrics fm(font1);

    painter.drawLine(start , end);
}
*/
