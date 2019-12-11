#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    void DrawRec(int x , int y , int w , int h , Qt::GlobalColor color  , QString text);
    void DrawCircle(QPoint c , int r , Qt::GlobalColor color  , QString text);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H