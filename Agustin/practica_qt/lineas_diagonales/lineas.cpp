#include <QMainWindow>
#include <QPainter>
#include <QLine>
#include <qapplication.h>

class MainWindow: public QMainWindow {
private:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        int height = this->height();
        int width= this->width();

        painter.setPen(Qt::green);
        QLine line1(0, 0, width - 1, height - 1);
        QLine line2(width - 1, 0, 0, height - 1);
        painter.drawLine(line1);
        painter.drawLine(line2);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
