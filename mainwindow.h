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
    QGroupBox* createAlgorithmBox();
    QGroupBox* createCalibrationBox();
    QGroupBox* createMouseBox();
    void initiateTimer();
    void cleanUp();

    // overriden methods
    void closeEvent(QCloseEvent *event);

private:
    //Ui::MainWindow *ui;

    // Widgets:
    QPushButton *startButton;
    QPushButton *stopButton;
    QComboBox *camerasCombo;

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

    //buttons
    void start();
    void stop();

};

#endif // MAINWINDOW_H
