#include <qapplication.h>
#include <QWidget>
#include <QPainter>
#include <QLine>

class Widget: public QWidget {
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        int height = this->height();
        int width = this->width();
        painter.setPen(Qt::red);
        //painter.setBrush(Qt::red);
        QPainterPath path;
        path.moveTo(width/3, 2*height/3);
        path.lineTo(2*width/3, 2*height/3);
        path.lineTo(width/2, height/3);
        path.lineTo(width/3, 2*height/3);
        painter.drawPath(path);
        painter.fillPath(path, QBrush(Qt::red));
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}
