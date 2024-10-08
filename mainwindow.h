#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colorhistogram.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString lastDir;
    ColorHistogram *hist;





public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void openFileSlot();


};
#endif // MAINWINDOW_H
