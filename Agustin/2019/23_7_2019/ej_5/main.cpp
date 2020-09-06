#include <iostream>
#include <QMainWindow>
#include <QPainter>
#include <main.moc>
//#include <qt5/QtWidgets/QMainWindow>
//#include <qt5/QtWidgets/qwidget.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
    Ui::MainWindow *ui;

public:
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
    }

    MainWindow::~MainWindow() {
        delete ui;
    }

    void MainWindow::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setBrush(Qt::DiagCrossPattern);

        QPen pen;

        pen.setColor(Qt::green);
        pen.setWidth(5);

        painter.setPen(pen);
        painter.drawRect(QRect(80,120,200,100));

    }

};

int main() {
    MainWindow m;
    return 0;
}
