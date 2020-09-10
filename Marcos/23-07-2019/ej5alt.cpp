/*5) Escriba una rutina que dibuje las dos diagonales de la pantalla en color rojo*/

#include <QApplication>
#include <QPainter>
#include <QWidget>

class Widget : public QWidget {
public:
    void paintEvent(QPaintEvent* event) override {
        double width = this->width();
        double height = this->height();
        QPainter painter(this);
        QPainterPath path;
        path.addEllipse({width/2, height/2}, 100, 100);
        /*
        path.moveTo(0, height - 1);
        path.lineTo(width - 1, height - 1);
        path.lineTo((width - 1)/2, 0);
        path.lineTo(0, height - 1);
        */
        painter.setPen(Qt::red);
        painter.fillPath(path, QBrush(Qt::yellow));
    }

};




int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Widget myWidget;
    myWidget.show();
    return app.exec();
}