#include <iostream>
#include "Warehouse.h"


int main() {

	//experimental code sample
	Warehouse warehouse(2);
	warehouse.Put("Cock");
	std::cout << warehouse.GetSize();
	return 0;
}