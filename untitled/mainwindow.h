#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "Parser.h"
#include "graphics.h"
#include "subwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /*
    virtual void paintEvent(QPaintEvent *event);
    QRect DrawRec(int x , int y , QString text);
    QRect DrawCircle(QPoint c , QString text);
    int  DrawTree(Node* root,int x,int y , QRect prev , string prev_type );
    void connectRectoChildRec(QRect rec1 , QRect rec2);
    void connectSiblingRects(QRect rec1 , QRect rec2);
    void connectRectoChildCir(QRect rec1 , QRect Ellipse);
    void connectCirtoChildCir(QRect Ellipse1 , QRect Ellipse2);
    void matchingLine(QPoint p1 , QPoint p2 , Qt::GlobalColor color);
    */
private slots:
    void InitUI();
    void browsefun();
    void DrawTree() ;

private:

    Ui::MainWindow *ui;
    QWidget *centralWidget;

    //colors and pallete
    QPalette *mainPalette;

    //Layouts
    QFormLayout *firstInputPage;
    QHBoxLayout *mainLayout;

    //PushButtons
    QPushButton *browse;
    QPushButton *Simulate;
    //label
    QLabel *firstPagetitle;

    string * directory;

   // SubWindow * subWindow;
    SubWindow *s1;
};

#endif // MAINWINDOW_H
