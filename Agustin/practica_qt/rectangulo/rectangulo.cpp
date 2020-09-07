#include <qapplication.h>
#include <QWidget>
#include <QPainter>

class Widget: public QWidget {
    void paintEvent(QPaintEvent* event) override {
    QPainter painter(this);
    int height = this->height();
    int width = this->width();
    painter.setPen(Qt::blue);
    painter.drawRect(width/4, height/4, width/4, height/4);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}
