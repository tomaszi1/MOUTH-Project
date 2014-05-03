#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    createMenu();

    // main layout:
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);
    // ui->setupUi(this);


    // left box:
    QWidget *leftBox = new QWidget;
    QVBoxLayout *leftBoxLayout = new QVBoxLayout;
    leftBox->setLayout(leftBoxLayout);
    leftBox->setStyleSheet("background-color:green;");

    QGroupBox *algorithmStartBox = new QGroupBox("Algorithm");


    //right box:
    QWidget *rightBox = new QWidget;
    QVBoxLayout *rightBoxLayout = new QVBoxLayout;
    rightBox->setLayout(rightBoxLayout);

    // add boxes to main layout:
    mainLayout->addWidget(leftBox,1);
    mainLayout->addWidget(rightBox,3);

    //set right box:
    textEdit = new QTextEdit;
    rightBoxLayout->addWidget(textEdit);


    // set central widget of QMainWindow
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenu(){

    saveAction = new QAction("Save", this);
    loadAction = new QAction("Load", this);
    quitAction = new QAction("Quit", this);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(load()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuFile = new QMenu("File");
    menuBar->addMenu(menuFile);
    menuFile->addAction(saveAction);
    menuFile->addAction(loadAction);
    menuFile->addAction(quitAction);

    setMenuBar(menuBar);
}

// Slots:
void MainWindow::save(){

}

void MainWindow::load(){

}

void MainWindow::quit(){
    QMessageBox messageBox;
    messageBox.setWindowTitle("Mouth");
    messageBox.setText(tr("Do you really want to quit?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    if (messageBox.exec() == QMessageBox::Yes)
        qApp->quit();
}
