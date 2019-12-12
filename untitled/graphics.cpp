#include "graphics.h"
#include <QKeyEvent>
#include <math.h>
#include "mainwindow.h"

Graphics::Graphics(QWidget *parent,string directory)
    : QGraphicsView(parent)
{
    this->setMouseTracking(true);
    this->setBackgroundRole(QPalette::Base);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0,5000,5000);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(scene);
    this->setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(AnchorUnderMouse);
    this->scale(qreal(0.8), qreal(0.8));
    this->setMinimumSize(400, 400);

    this->directory = new string;
    *(this->directory) = directory;
}



void Graphics::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}


#if QT_CONFIG(wheelevent)
void Graphics::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif



void Graphics::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Recursive Descent Parser Syntax Tree , zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(18);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);


    Parser p1;
    p1.read_file(*(this->directory));

    Node* Output = p1.statement_seq();
    if(Output == NULL){
        QMessageBox::warning(this,"Input File Error","The input file format is not correct");
        return;
    }
    else{
        DrawTree(Output,100,100,QRect(10,10,10,10),"None",painter);
    }
}

void Graphics::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void Graphics::zoomIn()
{
    scaleView(qreal(1.2));

}

void Graphics::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
/*
void Graphics:: paintEvent(QPaintEvent *painter)
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
*/
int Graphics:: DrawTree(Node* root,int x,int y , QRect prev , string prev_type , QPainter *painter){

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
        QRect newRec = DrawRec(x,y,text,painter);
        y = newRec.center().y() + (20+RECT_H);

        if(prev_type == "Rect"){
            connectRectoChildRec(prev,newRec,painter);
        }
        prev_type = "Rect";
        prev = newRec;
    }
    else if (root->drawn==false){
       if(root->type == "IDENTIFIER")
           text = "id(" +  QString::fromStdString(root->value) + ")";

       else if (root->type == "NUMBER")
           text = "const("  + QString::fromStdString(root->value) + ")";

       QRect newElipse = DrawCircle(QPoint(x,y),text,painter);
       y = newElipse.center().y()+2*RECT_H;

       if(prev_type == "Rect"){
           connectRectoChildCir(prev,newElipse,painter);
       }
       else if (prev_type == "Cir"){
           connectCirtoChildCir(prev,newElipse,painter);
       }
       prev_type = "Cir";
       prev = newElipse;
    }

    int x_move = 0 ;
    int max_children=0;
    int node_children;


    for(list<Node *>::iterator it=root->children.begin(); it != root->children.end(); it++){
       node_children =  DrawTree(*it, x+x_move, y , prev , prev_type,painter);
       if (max_children<node_children) max_children = node_children;
       x_move += 90 + (max_children) *90 ;
    }

    return root->children.size();

}

QRect Graphics:: DrawRec(int x , int y , QString text,QPainter * painter){
    //QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);

    //painter->setPen(pen);
    painter->setPen(pen);

    QRect rec1(x,y,RECT_W,RECT_H);
    QPoint r1_c = rec1.center();

    QFont font1("Volkhov",15,QFont::Light,true);
    //painter->setFont(font1);
    painter->setFont(font1);
    QFontMetrics fm(font1);

    int wfont = fm.width(text);
    r1_c = r1_c - QPoint(wfont/2 , 0);

    //painter->drawText(r1_c,  text);
    painter->drawText(r1_c,  text);
    pen.setColor(Qt::red);

    //painter->setPen(pen);
    painter->setPen(pen);
    //painter->drawRect(rec1);
    painter->drawRect(rec1);
    return rec1;
}

QRect Graphics:: DrawCircle(QPoint c , QString text,QPainter * painter){

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);

    painter->setPen(pen);

    QFont font1("Volkhov",13,QFont::Light,true);
    painter->setFont(font1);
    QFontMetrics fm(font1);

    int wfont = fm.width(text);
    QPoint Ctext = c - QPoint(wfont/2 , 0);

    QRect Ellipse (c.x() - Cir_R, c.y() - Cir_R, 2 * Cir_R, 2 * Cir_R);

    painter->drawText(Ctext,  text);

    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawEllipse(Ellipse);

    return Ellipse;
}

void Graphics :: connectRectoChildRec(QRect rec1 , QRect rec2,QPainter *painter){
    QPoint start = rec1.center() + QPoint(0,RECT_H/2);
    QPoint end = rec2.center() - QPoint(0,RECT_H/2);

    matchingLine(start , end ,Qt::blue,painter);
}
void Graphics :: connectRectoChildCir(QRect rec1 , QRect Ellipse,QPainter *painter){
    QPoint start = rec1.center() + QPoint(0,RECT_H/2);
    QPoint end = Ellipse.center() - QPoint(0,Cir_R);

    matchingLine(start , end ,Qt::blue,painter);
}

void Graphics :: connectCirtoChildCir(QRect Ellipse1 , QRect Ellipse2,QPainter *painter){
    QPoint start = Ellipse1.center() + QPoint(0,Cir_R);
    QPoint end = Ellipse2.center() - QPoint(0,Cir_R);

    matchingLine(start , end ,Qt::blue,painter);
}

void Graphics :: connectSiblingRects(QRect rec1 , QRect rec2,QPainter *painter){
    QPoint start = rec1.center() + QPoint(RECT_W/2,0);
    QPoint end = rec2.center() - QPoint(RECT_W/2,0);

    matchingLine(start , end ,Qt::blue,painter);
}
void Graphics :: matchingLine(QPoint start , QPoint end , Qt::GlobalColor color,QPainter *painter){
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);

    painter->setPen(pen);

    QFont font1("Volkhov",13,QFont::Light,true);
    painter->setFont(font1);
    QFontMetrics fm(font1);

    painter->drawLine(start , end);
}