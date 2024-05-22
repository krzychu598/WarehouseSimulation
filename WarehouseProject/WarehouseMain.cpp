#include <iostream>
#include "Warehouse.h"

// Zmienne z _ np. storage_space
// Funkcje camelCase
// Push to dev
// Podział StorageSpace po konsultacji ze wszystkimi
// Warehouse, Area - Krzychu; Shelving, Box - Maks; Product, Employee - Paweł
int main() {

	//experimental code sample
	Warehouse warehouse("WarehoseProject/warehouse.json");
	warehouse.put("Cock");
	std::cout << warehouse.getSize();
	return 0;
}