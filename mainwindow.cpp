#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera.h"
#include "videoqlabel.h"
#include "calibration.h"
#include "frame_holder.h"
#include "video_dispatch.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QWidget>
#include <QApplication>
#include <QFormLayout>




#include <QTimer>
#include <QCloseEvent>
#include <QGridLayout>

const int MainWindow::DEFAULT_FPS = 5;

// Constructor:
//*********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createMenu();

    // main layout:
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);
    // ui->setupUi(this);


    // left box:
    //**************************************************
    QWidget *leftBox = new QWidget(centralWidget);
    leftBox->setMinimumWidth(230);

    // create tabPanel:
    tabPanel = new QTabWidget(leftBox);

    // create Calibration Tab:
    createCalibrationTab(leftBox);

    // create General Tab:
    createGeneralTab(leftBox);




    //right box:
    //**************************************************
    QWidget *rightBox = new QWidget;

    // video box QLabel
    VideoQLabel *videoBox = new VideoQLabel(rightBox);
    videoBox->setActiveClick(true);
    videoBox->setText("Video stream window");

    QGridLayout *rightBoxLayout = new QGridLayout;
    rightBoxLayout->addWidget(videoBox);
    rightBox->setLayout(rightBoxLayout);
    rightBox->setStyleSheet("background-color:#e9e9e9;");

    // add boxes to main layout:
    mainLayout->addWidget(leftBox,1);
    mainLayout->addWidget(rightBox,3);

    // set central widget of QMainWindow
    setCentralWidget(centralWidget);

    // calibration measures
    calibration = new Calibration();
    FrameHolder *holder = new FrameHolder();
    calibration->setFrameHolder(holder);

    dispatcher = new VideoDispatcher();
    dispatcher->attach(videoBox);
    dispatcher->attach(holder);
    initiateTimer();
    connect(videoBox,SIGNAL(mousePressed(QPoint,QSize)),calibration,SLOT(receiveClickedPixel(QPoint,QSize)));
    calibration->setState(IN_PROGRESS);
}

// Destructor:
//*********************************************************************************************************************
MainWindow::~MainWindow()
{
}


// USER INTERFACE:
//*********************************************************************************************************************

// Create Menu:
void MainWindow::createMenu(){

    saveAction = new QAction("Save", this);
    loadAction = new QAction("Load", this);
    quitAction = new QAction("Quit", this);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(load()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menuFile = new QMenu("File",menuBar);
    menuBar->addMenu(menuFile);
    menuFile->addAction(saveAction);
    menuFile->addAction(loadAction);
    menuFile->addAction(quitAction);

    setMenuBar(menuBar);
}


// Create Left Panel:
void MainWindow::createGeneralTab(QWidget *parent)
{
    // create general page:
    generalTab = new QWidget(parent);
    QVBoxLayout *generalTabLayout = new QVBoxLayout();
    generalTab->setLayout(generalTabLayout);

    // create general page content:

    //create algorithm box:
    QGroupBox *algorithmBox = new QGroupBox("Algorithm:",generalTab);
    startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    stopButton = new QPushButton("End");
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    QFormLayout *formLayoutAlgorithm = new QFormLayout();
    algorithmBox->setLayout(formLayoutAlgorithm);

    formLayoutAlgorithm->addRow("Start algorithm:", startButton);
    formLayoutAlgorithm->addRow("Stop algorithm:",  stopButton);

    // add algorithmBox to mainLayout
    generalTabLayout->addWidget(algorithmBox);




    // create mouseBox:
    QGroupBox *mouseBox = new QGroupBox("Mouse:",generalTab);
    QFormLayout *formLayoutMouse = new QFormLayout();
    mouseBox->setLayout(formLayoutMouse);

    repositionButton = new QPushButton("Reposition");
    connect(repositionButton, SIGNAL(clicked()), this, SLOT(reposition()));
    resetButton = new QPushButton("Reset");
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    smoothnessSlider = new QSlider(Qt::Horizontal);
    smoothnessSlider->setMinimum(0);
    smoothnessSlider->setMaximum(100);
    smoothnessSlider->setTickInterval(10);
    smoothnessSlider->setValue(50);
    smoothnessSlider->setTickPosition(QSlider::TicksBelow);
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(0);
    speedSlider->setMaximum(100);
    speedSlider->setTickInterval(10);
    speedSlider->setValue(50);
    speedSlider->setTickPosition(QSlider::TicksBelow);

    formLayoutMouse->addRow("Smoothness:", smoothnessSlider);
    formLayoutMouse->addRow("Speed:", speedSlider);
    formLayoutMouse->addRow("Reposition Cursor:", repositionButton);
    formLayoutMouse->addRow("Reset settings:", resetButton);

    // add mousebox to main layout
    generalTabLayout->addWidget(mouseBox);


    // create saveFileBox:
/*
    QGroupBox *saveFileBox = new QGroupBox("Save: ", generalTab);
    QVBoxLayout *mainSaveBoxLayout = new QVBoxLayout();
    saveFileBox->setLayout(mainSaveBoxLayout);
    QWidget *saveLabelBox = new QWidget();
    QHBoxLayout *saveLabelLayout= new QHBoxLayout();
    saveLabelBox->setLayout(saveLabelLayout);
    QLabel *saveLabel= new QLabel("Save as: ");
    QTextEdit *saveFileText = new QTextEdit();
*/



    // add general page to tabPanel:
    tabPanel->addTab(generalTab,"General");
}

void MainWindow::createCalibrationTab(QWidget *parent)
{
    // create  calibration page:
    calibrationTab = new QWidget(parent);
    QVBoxLayout *calibrationMainLayout = new QVBoxLayout();
    calibrationTab->setLayout(calibrationMainLayout);

    // create calibration pagecontent:

    // create camera choose Box:

    QGroupBox *cameraBox = new QGroupBox("Camera: ");
    QFormLayout *cameraFormLayout = new QFormLayout();
    cameraBox->setLayout(cameraFormLayout);
    switchCameraButton = new QPushButton("Switch");
    connect(switchCameraButton,SIGNAL(clicked()),this,SLOT(switchCamera()));
    cameraFormLayout->addRow("Switch camera:", switchCameraButton);
    //add camera box to calibrationmainLayout:
    calibrationMainLayout->addWidget(cameraBox);

    // add calibration page to tabPanel
    tabPanel->addTab(calibrationTab,"Calibration");
}

// methods:
//*********************************************************************************************************************

void MainWindow::initiateTimer(){
    paintTimer = new QTimer(this);
    connect(paintTimer,SIGNAL(timeout()),dispatcher,SLOT(dispatchFrame()));
    paintTimer->start(1000/DEFAULT_FPS);
}

void MainWindow::closeEvent(QCloseEvent *event){
    quit();
}


void MainWindow::cleanUp(){
    paintTimer->stop();
    delete dispatcher;
}


// Slots:
//*********************************************************************************************************************
void MainWindow::save(){

}

void MainWindow::load(){

}

void MainWindow::quit(){
    /*QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Mouth", "Do you really want to quit?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes){
        cleanUp();
        qApp->quit();
    }*/
    cleanUp();
    qApp->quit();
}

// butons:
void MainWindow::start(){

}

void MainWindow::stop(){

}

void MainWindow::reposition()
{

}

void MainWindow::reset()
{


}

void MainWindow::switchCamera()
{
    Camera *camera = Camera::getInstance();
    camera->switchCamera();
}
