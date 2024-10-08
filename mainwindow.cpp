#include "mainwindow.h"

#include  <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    QAction *openFileAct = new QAction("&Open image file");
    connect(openFileAct, &QAction::triggered, this, &MainWindow::openFileSlot);
    openFileAct->setShortcut(Qt::CTRL | Qt::Key_O);

    QMenu *fileMenu = new QMenu("&File");
    fileMenu->addAction(openFileAct);
    menuBar()->addMenu(fileMenu);

    QSettings settings("Pezza Productions", "ColorHist1");
    lastDir = settings.value("lastDir", "").toString();


}

MainWindow::~MainWindow() {}


void MainWindow::openFileSlot(){
    QString fName = QFileDialog::getOpenFileName(this, "Select image file", lastDir, "Image files (*.png *.jpeg *.jpg *.bmp)");
    if (fName.isEmpty()) return;

    QImage image(fName);
    if (image.isNull()) return;

    lastDir = QFileInfo(fName).absolutePath();

    hist = new ColorHistogram(image);
    setCentralWidget(hist);


}
