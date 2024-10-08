#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QVector>

class ColorHistogram : public QWidget
{
    Q_OBJECT

    QImage image;
    QPixmap defaultPixmap;
    QLabel *histogramLabel;
    QSlider *slider;
    QComboBox *colorSelect;
    QComboBox *scaleSelect;
    QVector<QPixmap> pixmapCube;
    QVector<int> colorFrequencies;




public:
    explicit ColorHistogram(const QImage &_image);

    void buildPixmap();

signals:


public slots:

    void sliderMoved();
    void comboBoxChanged();

};

#endif // COLORHISTOGRAM_H
