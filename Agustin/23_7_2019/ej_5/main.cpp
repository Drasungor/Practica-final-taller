#include <iostream>
#include <QMainWindow>
#include <QPainter>
//#include <qt5/QtWidgets/QMainWindow>
//#include <qt5/QtWidgets/qwidget.h>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0): QMainWindow(parent) {
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setBrush(Qt::DiagCrossPattern);

        QPen pen;

        pen.setColor(Qt::green);
        pen.setWidth(5);

        painter.setPen(pen);
        painter.drawRect(QRect(80,120,200,100));
    }

    ~MainWindow() override = default;

};

int main() {
    MainWindow m;
    return 0;
}
