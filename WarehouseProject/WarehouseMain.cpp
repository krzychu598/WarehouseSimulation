#include <iostream>
#include "Warehouse.h"


// Zmienne z _ np. storage_space
// Funkcje camelCase
// Push to dev
// Podział StorageSpace po konsultacji ze wszystkimi
// Warehouse, Area - Krzychu; Shelving, Box - Maks; Product, Employee - Paweł
int main() {
	
	//experimental code sample
	Warehouse warehouse("../warehouse.json");
	warehouse.put("Foo", "Electronics");
	if (warehouse.find("Foo", "Electronics") == true) {
		std::cout << "object found\n";
	}
	else {
		std::cout << "object not found\n";
	};
	return 0;
}