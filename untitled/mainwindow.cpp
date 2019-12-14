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
    directory = new string ();
    *directory = filename.toStdString();

}
void MainWindow:: DrawTree(){

    if(*directory == ""){
        QMessageBox::warning(this,"Input File Error","Please Select an input file");
        return;
    }
    P1 = new Parser();
    P1->read_file(*(this->directory));
    Node* output = P1->statement_seq();

    if(output == NULL){
        QMessageBox::warning(this,"Syntax Error","The Statements are not accepted by TINY language");
        return;
    }
    else{
        s1 = new SubWindow(this,output);
        s1->setModal(true);
        s1->setWindowTitle("Syntax Tree");
        s1->setFixedSize(QSize(1050,600));
        s1->exec();
    }
}
