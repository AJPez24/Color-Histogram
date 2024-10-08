#include "colorhistogram.h"

#include "imageviewer.h"
#include <QHBoxLayout>
#include <QVector>


ColorHistogram::ColorHistogram(const QImage &_image):image(_image), colorFrequencies(1 << 24, 0), defaultPixmap(256, 256), pixmapCube(256){


    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    ImageViewer *imageViewer = new ImageViewer(_image);
    mainLayout->addWidget(imageViewer);


    QWidget *rightSide = new QWidget();
    mainLayout->addWidget(rightSide);


    QVBoxLayout *toolBar = new QVBoxLayout(rightSide);

    histogramLabel = new QLabel();
    histogramLabel->setPixmap(defaultPixmap);
    toolBar->addWidget(histogramLabel,  0, Qt::AlignCenter);

    slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(255);
    slider->setMinimumWidth(256);
    connect(slider, &QSlider::sliderMoved, this, &ColorHistogram::sliderMoved);
    toolBar->addWidget(slider, 0, Qt::AlignCenter);

    colorSelect = new QComboBox();
    colorSelect->addItem("Red");
    colorSelect->addItem("Green");
    colorSelect->addItem("Blue");
    connect(colorSelect, &QComboBox::currentTextChanged, this, &ColorHistogram::comboBoxChanged);
    toolBar->addWidget(colorSelect,  0, Qt::AlignCenter);

    scaleSelect = new QComboBox();
    scaleSelect->addItem("1");
    scaleSelect->addItem("2");
    scaleSelect->addItem("4");
    scaleSelect->addItem("8");
    scaleSelect->addItem("16");
    scaleSelect->addItem("32");
    scaleSelect->addItem("64");
    scaleSelect->addItem("128");
    scaleSelect->addItem("256");
    connect(scaleSelect, &QComboBox::currentTextChanged, this, &ColorHistogram::comboBoxChanged);
    toolBar->addWidget(scaleSelect,  0, Qt::AlignCenter);


    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb currentColor = image.pixel(x, y);
            ++colorFrequencies[currentColor & 0xffffff];
        }
    }


    buildPixmap();

}


void ColorHistogram::buildPixmap(){

    if (colorSelect->currentText() == "Red"){
        for (int i = 0; i < 256; ++i){

            QImage blank(256, 256, QImage::Format_RGB32);

            for (int row = 0; row < 256; ++row){

                for (int col = 0; col < 256; ++col){

                    QRgb currentColor = qRgb(i, col, row) & 0xffffff;
                    int scale = scaleSelect->currentText().toInt() * colorFrequencies[currentColor];
                    if (scale > 255){
                        scale = 255;
                    }
                    blank.setPixel(col, row, 0x010101 * scale);

                }
            }

            pixmapCube[i] = QPixmap::fromImage(blank);
        }
    }
    else if (colorSelect->currentText() == "Green"){
        for (int i = 0; i < 256; ++i){

            QImage blank(256, 256, QImage::Format_RGB32);

            for (int row = 0; row < 256; ++row){

                for (int col = 0; col < 256; ++col){

                    QRgb currentColor = qRgb(col, i, row) & 0xffffff;
                    int scale = scaleSelect->currentText().toInt() * colorFrequencies[currentColor];
                    if (scale > 255){
                        scale = 255;
                    }
                    blank.setPixel(col, row, 0x010101 * scale);

                }
            }

            pixmapCube[i] = QPixmap::fromImage(blank);
        }
    }
    else{
        for (int i = 0; i < 256; ++i){

            QImage blank(256, 256, QImage::Format_RGB32);

            for (int row = 0; row < 256; ++row){

                for (int col = 0; col < 256; ++col){

                    QRgb currentColor = qRgb(col, row, i) & 0xffffff;
                    int scale = scaleSelect->currentText().toInt() * colorFrequencies[currentColor];
                    if (scale > 255){
                        scale = 255;
                    }
                    blank.setPixel(col, row, 0x010101 * scale);
                }
            }

            pixmapCube[i] = QPixmap::fromImage(blank);
        }
    }


    sliderMoved();

}

void ColorHistogram::sliderMoved(){
    histogramLabel->setPixmap(pixmapCube[slider->sliderPosition()]);
}


void ColorHistogram::comboBoxChanged(){
    buildPixmap();
}






















