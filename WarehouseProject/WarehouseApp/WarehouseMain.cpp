#include <iostream>
#include "Warehouse.h"
#include "Product.h"
#include "Employee.h"
// Zmienne z _ np. storage_space
// Funkcje camelCase
// Push to dev
// Podział StorageSpace po konsultacji ze wszystkimi
// Warehouse, Area - Krzychu; Shelving, Box - Maks; Product, Employee - Paweł

int main() {

	//experimental code sample
	
	Warehouse warehouse("warehouse_data.json");
	
	warehouse.acceptDelivery("delivery1.json");
	warehouse.acceptDelivery("delivery2.json");
	warehouse.acceptDelivery("delivery3.json");

	warehouse.sendDelivery("request1.json");

	return 0;

}



/*
Example Log:
Warehouse Amaze-On created				(appropiate json file given to a warehouse constructor)
Initial state of the warehouse restored (All products from json file initiated)
New incoming delivery accepted / Delivery not accepted (size of every type of product caculated and compared with the size of the area, if delivery is accepted boxes objects are created)
Unloading delivery:
Employee A transports 3 Boxes to Area Electronics
Employee B transports 2 Boxes to Area Food&Drink
...
New outgoing delivery

*/
