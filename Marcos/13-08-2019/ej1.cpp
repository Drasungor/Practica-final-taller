#include <qapplication.h>
//#include <qpushbutton.h>
#include <QPainter>
#include <QWidget>
#include <QLine>

/*1) Escriba una rutina que dibuje un triangulo amarillo del tamanio de la
ventana*/

class Widget : public QWidget {
protected:
    void paintEvent(QPaintEvent *event) override { /*redefinimos esta funcion para poder pintar, sino Qt no dibuja una mierda*/
        QPainter painter(this);
        int height = this->height();
        int width = this->width();
        /*
        QLine line1(0, height - 1, width, height - 1);
        QLine line2(0, height, width / 2, 0);
        QLine line3(width / 2, 0, width, height);

        painter.setPen(Qt::yellow);
        painter.drawLine(line1);
        painter.drawLine(line2);
        painter.drawLine(line3); //esto es para dibujar el triangulo sin relleno, forma alternativa al drawPath
        */
        QPainterPath path;
        // Set pen to this point.
        path.moveTo(0, height - 1);
        path.lineTo(width, height - 1); /*move here*/
        path.lineTo(width / 2, 0); /*move here*/
        path.lineTo (0, height - 1);
        //painter.setPen(Qt::yellow); //esto es para el drawPath
        //painter.drawPath(path); esta linea dibuja el triangulo sin relleno
        painter.fillPath(path, QBrush(QColor("yellow"))); /*dibujar triangulo con relleno*/
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}