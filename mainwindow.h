#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createMenu();
    QGroupBox* createAlgorithmBox();
    QGroupBox* createCalibrationBox();
    QGroupBox* createMouseBox();

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

private slots:
    void save();
    void load();
    void quit();

    //buttons
    void start();
    void stop();
};

#endif // MAINWINDOW_H
