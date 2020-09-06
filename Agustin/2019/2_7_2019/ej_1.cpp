#include <string>
#include <iostream>

class Numero {
private:
	std::string num_string;
	
public:
	Numero(unsigned long numero_inicial){
		num_string = std::to_string(numero_inicial);
	}	

	Numero() {
		num_string = "0";
	}

	Numero(Numero&& other) {
		num_string = std::move(other.num_string);
	}

	Numero& operator=(const Numero& other) {
		num_string = other.num_string;
		return *this;
	}

	Numero& operator<<(const std::string& numero) {
		num_string += numero;
		return *this;
	}
	
	void operator()() {
		std::cout << num_string;
	}
	
	operator long() {
		return std::stol(num_string);
	}

	Numero& operator++() {
		unsigned long aux = std::stol(num_string);
		aux++;
		num_string = std::to_string(aux);
		return *this;
	}
	
	Numero& operator>>(Numero& other){
		std::string aux = num_string;
		aux += other.num_string;
		other.num_string = std::move(aux);
		return *this;
	}
};

int main(int argc, const char* argv[]) {
	return 0;
}
