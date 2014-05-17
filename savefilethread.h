#ifndef SAVEFILETHREAD_H
#define SAVEFILETHREAD_H

#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class saveFileThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;

    int loop_number;
    string file;

public:
    saveFileThread(int times, string filename);
};

#endif // SAVEFILETHREAD_H
