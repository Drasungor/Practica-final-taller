#include <qapplication.h>
#include <QWidget>
#include <QPainter>

class Widget: public QWidget {
private:
    void paintEvent(QPaintEvent* event) {
        QPainter painter(this);
        int width = this->width();
        int height = this->height();
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPoint(width/2, height/2), width/4, width/4);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();
    return app.exec();
}
