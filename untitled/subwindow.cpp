#include "subwindow.h"
#include "ui_subwindow.h"

SubWindow::SubWindow(QWidget *parent,string directory) :
    QDialog(parent),
    ui(new Ui::SubWindow)
{
    ui->setupUi(this);

    mainPalette = new QPalette;
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);

    UI_init(directory);
}

SubWindow::~SubWindow()
{
    delete ui;
}

void SubWindow::UI_init(string directory)
{

    widget = new Graphics(0, directory);

    //remove border of the Graph layout
    widget->setStyleSheet("border:0px;");

    QFont font2("Volkhov",11,QFont::Light,true);


    TreeLayout = new QHBoxLayout;
    TreeLayout -> addWidget(widget);


    //adding main layout to central widget of window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(TreeLayout);


}
