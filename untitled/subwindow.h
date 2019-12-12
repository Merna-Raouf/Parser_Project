#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QDialog>
#include <QPainter>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <QFileDialog>
#include "Parser.h"
#include "graphics.h"

namespace Ui {
class SubWindow;
}

class SubWindow : public QDialog
{
    Q_OBJECT
private slots:
     void UI_init(string directory);
public:
     SubWindow(QWidget *parent = 0,string directory="");
    ~SubWindow();

private:
    Ui::SubWindow *ui;

    //colors and pallete
    QPalette *mainPalette;

    QWidget *centralWidget;

    //tree widget
    Graphics *widget;
    QHBoxLayout *TreeLayout;
};

#endif // SUBWINDOW_H
