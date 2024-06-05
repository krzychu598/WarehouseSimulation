#include <iostream>
#include <thread>
#include <chrono>
#include "Warehouse.h"
#include "Product.h"
#include "Employee.h"
// Zmienne z _ np. storage_space
// Funkcje camelCase
// Push to dev
// Podział StorageSpace po konsultacji ze wszystkimi
// Warehouse, Area - Krzychu; Shelving, Box - Maks; Product, Employee - Paweł

//semantics - type - ("electronics", "industrial") type of product
//			  kind - ("Laptop", "Apple", "Paint") general name for product of some type
//			product- ("Razer Blade 15", "Sony WH-1000XM4", "Coca-Cola Zero Sugar") - specific product of some kind
void initiateLoop(Warehouse& warehouse) {
	int n;	
	while (true) {
		n = 5; //15 requests for 3 deliveries
		while (n != 0) {
			warehouse.sendDelivery("request1.json");
			warehouse.sendDelivery("request2.json");
			warehouse.sendDelivery("request3.json");
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			n--;
		}
		warehouse.acceptDelivery("delivery1.json");
		warehouse.acceptDelivery("delivery3.json");
		warehouse.acceptDelivery("delivery2.json");
	}
}

int main() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));	//wait for BoxGenerator to generate initial delivery
	Warehouse warehouse("warehouse_data.json");
	warehouse.acceptDelivery("delivery_initial.json");
	initiateLoop(warehouse);

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
