/*5) Escriba una rutina que dibuje las dos diagonales de la pantalla en color rojo*/

#include <qapplication.h>
#include <QPainter>
#include <QWidget>
#include <QLine>

class Widget : public QWidget {
public:
    void paintEvent(QPaintEvent* event) override {
        int height = this->height();
        int width = this->width();
        QPainter painter(this);
        /*
        QLine line1(0, 0, width, height - 1); //una forma de hacerlo
        QLine line2(0, height - 1, width, 0);
        painter.setPen(Qt::red);
        painter.drawLine(line1);
        painter.drawLine(line2);
        */
        QPainterPath path; //otra forma de hacerlo
        path.moveTo(0, 0);
        path.lineTo(width, height - 1);
        path.moveTo(0, height - 1);
        path.lineTo(width, 0);
        painter.setPen(Qt::red);
        painter.drawPath(path);
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}