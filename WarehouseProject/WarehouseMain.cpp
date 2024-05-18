#include <iostream>
#include "Warehouse.h"

// Zmienne z _ np. storage_space
// Funkcje getSpace, GetSpace?
// Push to dev
// Podział StorageSpace po konsultacji ze wszystkimi
// Warehouse, Area - Krzychu; Shelving, Box - Maks; Product, Employee - Paweł
int main() {

	//experimental code sample
	Warehouse warehouse(2);
	warehouse.Put("Cock");
	std::cout << warehouse.GetSize();
	return 0;
}