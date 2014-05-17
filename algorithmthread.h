#ifndef ALGORITHMTHREAD_H
#define ALGORITHMTHREAD_H

#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class algorithmThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;

public:
    algorithmThread();

private slots:
    void endAndCleanThread();
};

#endif // ALGORITHMTHREAD_H
