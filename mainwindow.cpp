#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>

// Constructor:
//*********************************************************************************************************************
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
    leftBox->setStyleSheet("background-color:#e9e9e9;");

    QGroupBox *algorithmStartBox = createAlgorithmBox();
    leftBoxLayout->addWidget(algorithmStartBox);

    QGroupBox *calibrationBox = createCalibrationBox();
    leftBoxLayout->addWidget(calibrationBox);

    QGroupBox *mouseBox = createMouseBox();
    leftBoxLayout->addWidget(mouseBox);


    //right box:
    QWidget *rightBox = new QWidget;
    QVBoxLayout *rightBoxLayout = new QVBoxLayout;
    rightBox->setLayout(rightBoxLayout);
    rightBox->setStyleSheet("background-color:#e9e9e9;");

    // add boxes to main layout:
    mainLayout->addWidget(leftBox,1);
    mainLayout->addWidget(rightBox,3);


    // set central widget of QMainWindow
    setCentralWidget(centralWidget);
}

// Destructor:
//*********************************************************************************************************************
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

// methods:
//*********************************************************************************************************************

QGroupBox* MainWindow::createAlgorithmBox(){

    QGroupBox *algorithmStartBox = new QGroupBox("Algorithm:");
    startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));

    QWidget *comboWidget = new QWidget;
    QLabel *comboLabel = new QLabel("Choose camera:");
    QHBoxLayout *comboLayout = new QHBoxLayout;
    camerasCombo= new QComboBox;
    /***************************************************************
     *
     * Napisać kod znajdujący kamery
     *
     *
     * *************************************************************/
    camerasCombo->addItem("A");
    camerasCombo->addItem("B");
    camerasCombo->addItem("C");
    comboLayout->addWidget(comboLabel);
    comboLayout->addWidget(camerasCombo);
    comboWidget->setLayout(comboLayout);

    stopButton = new QPushButton("Stop");
    connect(stopButton,SIGNAL(clicked()), this, SLOT(stop()));

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(startButton);
    boxLayout->addWidget(comboWidget);
    boxLayout->addWidget(stopButton);

    algorithmStartBox->setLayout(boxLayout);

    return algorithmStartBox;
}

QGroupBox* MainWindow::createCalibrationBox(){

    QGroupBox *algorithmCalibrationBox = new QGroupBox("Calibration:");


    return algorithmCalibrationBox;
}

QGroupBox* MainWindow::createMouseBox(){

    QGroupBox *algorithmMouseBox = new QGroupBox("Mouse:");

    return algorithmMouseBox;
}



// Slots:
//*********************************************************************************************************************
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

// butons:
void MainWindow::start(){

}

void MainWindow::stop(){

}
