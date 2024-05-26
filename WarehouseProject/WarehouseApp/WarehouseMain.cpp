#include <iostream>
#include "Warehouse.h"

// Zmienne z _ np. storage_space
// Funkcje camelCase
// Push to dev
// Podział StorageSpace po konsultacji ze wszystkimi
// Warehouse, Area - Krzychu; Shelving, Box - Maks; Product, Employee - Paweł
int main() {

	//experimental code sample
	Warehouse warehouse("warehouse_data.json");
	warehouse.put("Foo", "Electronics");
	if (warehouse.find("Foo", "Electronics") == true) {
		std::cout << "object found\n";
	}
	else {
		std::cout << "object not found\n";
	};
	return 0;

}



/*
Example Log:
Warehouse Amaze-On created				(appropiate json file given to a warehouse constructor)
Initial state of the warehouse restored (All products from json file initiated)
New delivery accepted / Delivery not accepted (size of every tyope of product caculated and compared with the size of the area, if delicery is accepted boxes objects are created)
Unloading delivery:
Employee A transports 3 Boxes to Area Electronics
Employee B transports 2 Boxes to Area Food&Drink


*/
