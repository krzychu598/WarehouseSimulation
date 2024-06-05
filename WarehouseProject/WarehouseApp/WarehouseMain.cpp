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


int main() {
	std::this_thread::sleep_for(std::chrono::seconds(2));																		//wait for BoxGenerator to generate initial delivery
	Warehouse warehouse("warehouse_data.json");																					//create Warehouse instance
	warehouse.acceptDelivery("delivery_initial.json", true);																	//restore initial warehouse inventory
	std::vector<std::string> deliveries{ "delivery1.json", "delivery2.json", "delivery3.json" };								//initialize set of possible deliveries
	std::vector<std::string> requests {"request1.json", "request2.json", "request3.json", "request4.json", "request5.json", };	//initialize set of possible requests
	warehouse.startWorking(deliveries, requests);																				//start program loop
	return 0;

}
