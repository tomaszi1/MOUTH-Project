#include "savefilethread.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <QMessageBox>
#include <iostream>
#include <camera.h>

using namespace cv;

saveFileThread::saveFileThread(int times, string filename)
{
    loop_number = times;
    file = filename;
}

void saveFileThread::run()
{
    Mat *frame;                                 // do przechowywania obrazka
    Camera *cam = Camera::getInstance();        // instancja kamery
    double width = cam->getWidth();             // potrzebne parametry kamery
    double height = cam->getHeight();

    //stworzenie obiektu VideoWriter:
    VideoWriter video(file,-1, 30, cvSize((int)width,(int)height), true);

    // sprawdzenie czy plik do zapisu został otwarty:
    if(!video.isOpened())
    {
        std::cout<< "błąd otwarcia pliku" << std::endl;
        return;
    }

    int i =0;
    std::cout << "zapis" << std::endl;
    // zapisywanie do pliku:
    while(i< loop_number * 300)
    {
        // pobranie klatki z kamery:
        frame = cam->read();

        // sprawdzenie czy klatka została pobrana:
        if(frame->data == NULL){
            std::cout << "klatka pusta" << std::endl;
            video.release();
            return;
        }

        // zapis do pliku:
        video.write(*frame);
        std::cout << i << std::endl;
        i++;
    }
    video.release();
    std::cout << "to ja thread! " << loop_number << std::endl;
}
