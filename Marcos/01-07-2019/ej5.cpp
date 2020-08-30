/*5) Declare una clase de eleccion libre. Incluya todos los campos de datos
requeridos con su correcta exposicion/publicacion, y los operadores ++, -, ==,
>> (carga), << (impresion), constructor move y operador float().*/

#include <iostream>
#include <string>

class Student {
public:
    std::string name;
    int age;
    int gpa;

public:
    Student(const std::string& _name, const int _age, const int _gpa) {
        name = _name;
        age = _age;
        gpa = _gpa;
    }

    Student(Student&& other) noexcept {
        name = std::move(other.name);
        age = other.age;
        gpa = other.gpa;
        other.age = 0;
        other.gpa = 0;
    }

    Student& operator++() {
        ++age;
        ++gpa;
        return *this;
    }

    Student operator-(const Student& other) const {
        Student result(name, age - other.age, gpa - other.gpa);
        return result;
    }

    bool operator==(const Student& other) const {
        return (name == other.name && age == other.age && gpa == other.gpa);
    }

    operator float() { /*si le agregas explicit al principio tenes que poner explicitamente el casteo tipo static_cast<float> o (float)*/
        return (age + gpa);
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student);

    friend std::istream& operator>>(std::istream& is, Student& student);

};

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << student.name << " " << student.age << " " << student.gpa;
    return os;
}

std::istream& operator>>(std::istream& is, Student& student) {
    is >> student.name >> student.age >> student.gpa;
    return is;
}

int main() {
    Student first("carlos", 3, 5);
    Student second("jose", 1, 2);
    Student result = first - second;
    std::cout << result << std::endl;
    return 0;
}
