#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>


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

private:
    //Ui::MainWindow *ui;

    // Widgets:
    QTextEdit *textEdit;

    // settings/menu:
    QAction *saveAction;
    QAction *loadAction;
    QAction *quitAction;

private slots:
    void save();
    void load();
    void quit();
};

#endif // MAINWINDOW_H
