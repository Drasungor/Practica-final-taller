/*3) Explique que es y para que sirve una variable de clase (o atributo estatico)
en C++. Mediante un ejemplo de uso, indique como se define dicha variable,
su inicializacion y el acceso a su valor para realizar una impresion simple
dentro de un main.*/

/*Una variable de clase/atributo estatico es un dato que vive en el data segment,
por lo que se reserva memoria para este dato al inicio del programa y se libera
al final del programa. Dicho dato se comparte entre todas las instancias de la clase
a la que pertenezca, por lo que se lo suele llamar "variable/atributo de clase".
*/

/*Ejemplo*/

#include <iostream>

class Foo {
private:
    static int someNumber; /*Declaracion de la variable de clase*/

public:
    static void print() {
        std::cout << someNumber << std::endl;
    }
};

int Foo::someNumber = 0; /*inicializacion*/

int main() {
    Foo::print(); /*Vemos que podemos utilizar las variable de clase en los metodos de clase*/
    return 0;
}