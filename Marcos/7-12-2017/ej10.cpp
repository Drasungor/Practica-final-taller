/*10) Escriba una rutina que muestre un boton y un cuadro de texto en una
ventana. Al hacer click en el boton debe desaparecer el cuadro de texto,
dejando el resto de la ventana intacta*/

/*Las cosas comentadas son del ejemplo de Mati de GitHub que use para aprender*/

/*NO SE COMO PORONGA HACER QUE NO CAMBIE DE FORMA TODO LO OTRO. DE BAJA ESO*/

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QObject>

class Widget : public QWidget {
private:
    //QLabel labelOut;
    QPushButton button;
    QLineEdit textBox;

public:
    explicit Widget(QWidget* parent = 0) : QWidget(parent), button("Borrar cuadro") {
        //QVBoxLayout* widgetLayout = new QVBoxLayout();
        QHBoxLayout* inputLayout = new QHBoxLayout();

        inputLayout->addWidget(&this->textBox);
        inputLayout->addWidget(&this->button);
        //widgetLayout->addLayout(inputLayout);
        //greeterLayout->addWidget(&this->labelOut);
        //this->labelOut.setText("Ingrese un nombre");
        this->setLayout(inputLayout);
        //QObject::connect(&this->buttonGreet, &QPushButton::clicked, this,
        //                &Widget::updateGreetings);
        QObject::connect(&this->button, &QPushButton::clicked, this, &Widget::deleteTextBox);
    }

private:
    /*
    void updateGreetings() {
        QString name = this->inputName.text();
        QString greetings = QString("Hola %1").arg(name);
        this->labelOut.setText(greetings);
    }
    */
    void deleteTextBox() {
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); /*no funca*/
        this->layout()->setSizeConstraint(QLayout::SetFixedSize);
        textBox.setVisible(false);
    }

};


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Widget widget;
    widget.show();

    return app.exec();
}