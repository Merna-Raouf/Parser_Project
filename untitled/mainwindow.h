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

    //pointer to parser object
    Parser *P1;

   // SubWindow * subWindow;
    SubWindow *s1;
};

#endif // MAINWINDOW_H
