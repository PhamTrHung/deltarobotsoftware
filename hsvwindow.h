#ifndef HSVWINDOW_H
#define HSVWINDOW_H

#include <QDialog>
#include <QSlider>
#include <QLabel>

namespace Ui {
class HSVWindow;
}

class HSVWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HSVWindow(QWidget *parent = nullptr);
    ~HSVWindow();

    void initEvents();
    void initVariables();

    QSlider* sliderWidget[6];
    QLabel* lblSliderValue[6];

public slots:
    void updateSliderValue();

signals:
    void valueChanged(int minH, int maxH, int minS, int maxS, int minV, int maxV);

private:
    Ui::HSVWindow *ui;
};

#endif // HSVWINDOW_H
