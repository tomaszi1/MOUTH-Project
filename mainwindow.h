#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QComboBox>
#include "camera.h"
#include "video_dispatch.h"
#include "calibration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static const int DEFAULT_FPS = 30;

private:
    void createMenu();
    void createGeneralTab(QWidget *parent);
    void createCalibrationTab(QWidget *parent);
    QGroupBox* createAlgorithmBox();
    QGroupBox* createCalibrationBox();
    QGroupBox* createMouseBox();
    void initiateTimer();
    void cleanUp();

    // overriden methods
    void closeEvent(QCloseEvent *event);

private:
    //Ui::MainWindow *ui;

    // Widgets UI:
    //*********************

    // LeftBox:
    QTabWidget *tabPanel;
    QWidget *generalTab;
    QWidget *calibrationTab;
    // algorithm:
    QPushButton *startButton;
    QPushButton *stopButton;

    // mouse:
    QSlider *smoothnessSlider;
    QSlider *speedSlider;
    QPushButton *resetButton;
    QPushButton *repositionButton;
    // calibration:
    QPushButton *switchCameraButton;





    //***********************

    // settings/menu:
    QAction *saveAction;
    QAction *loadAction;
    QAction *quitAction;

    // invokes painting video frames
    QTimer *paintTimer;

    // camera access
    Camera *camera;

    // dispatches video from camera to listeners
    VideoDispatcher *dispatcher;

    Calibration *calibration;

private slots:
    void save();
    void load();
    void quit();
    void reposition();
    void reset();

    //buttons
    void start();
    void stop();
    void switchCamera();

};

#endif // MAINWINDOW_H
