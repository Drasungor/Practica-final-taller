#include <qapplication.h>
//#include <qpushbutton.h>
#include <QPainter>
#include <QWidget>
#include <QLine>

/*Dibujar un triangulo amarillo del tamanio de la ventana*/

class Widget : public QWidget {
protected:
    void paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        int height = this->height();
        int width = this->width();
        QLine line1(0, height - 1, width, height - 1);
        QLine line2(0, height, width / 2, 0);
        QLine line3(width / 2, 0, width, height);
        painter.setPen(Qt::yellow);
        painter.drawLine(line1);
        painter.drawLine(line2);
        painter.drawLine(line3);
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}