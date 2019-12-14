#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsView>
#include "Parser.h"
#define RECT_H 80   // rectangle height
#define RECT_W 100 // rectangle width
#define Cir_R 35

class Graphics :public QGraphicsView
{
public:
    Graphics(QWidget *parent = 0,string directory="");

    //virtual void paintEvent(QPaintEvent *painter) ;
    QRect DrawRec(int x , int y , QString text,QPainter * painter);
    QRect DrawCircle(QPoint c , QString text,QPainter * painter);
    int  DrawTree(Node* root,string prev_val,string pre_prev,int pre_flag,int flag,int x,int y , QRect prev , string prev_type , QPainter *painter );
    void connectChildRec(QRect rec1 , QRect rec2,QPainter *painter);
    void connectSiblingRects(QRect rec1 , QRect rec2,QPainter *painter);
    void matchingLine(QPoint p1 , QPoint p2 , Qt::GlobalColor color,QPainter * painter);
    int count_leaf(Node* root);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);
private:
    QGraphicsScene *scene;

    string * directory;
};

#endif // GRAPHICS_H
