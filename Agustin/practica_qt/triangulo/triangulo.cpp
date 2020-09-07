#include <qapplication.h>
#include <QWidget>
#include <QPainter>

class Widget: public QWidget {
private:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        int width = this->width();
        int height = this->height();
        painter.setPen(Qt::blue);
        QPainterPath path;
        path.moveTo(width/3, 2 * height/3);
        path.lineTo(2*width/3, 2*height/3);
        path.lineTo(width/2, height/3);
        path.lineTo(width/3, 2*height/3);
        painter.drawPath(path);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}
