#include <qapplication.h>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>

class Greeter: public QWidget {
public:
    explicit Greeter(QWidget* parent = 0): QWidget(parent), button("saludar") {}

private:
    Greeter(QPaintEvent* event) {
        QHBoxLayout* h_layout = new QHBoxLayout();
        QVBoxLayout* v_layout = new QVBoxLayout();
        h_layout->addWidget(&txt_box);
        h_layout->addWidget(&button);
        v_layout->addLayout(h_layout);
        v_layout->addWidget(&label_out);
        setLayout(v_layout);
        label_out.setText("Escriba un nombre");
        QObject::connect(&button, &QPushButton::clicked, this, &Greeter::update_greetings);
    }

    void update_greetings() {
        QString string_aux = txt_box.text();
        label_out.setText(QString(QString("Hola %1").arg(string_aux)));
    }

private:
    QLabel label_out;
    QLineEdit txt_box;
    QPushButton button;
};


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Greeter greeter;
    greeter.show();
    return app.exec();
}
