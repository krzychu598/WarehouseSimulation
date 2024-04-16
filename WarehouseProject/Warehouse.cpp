#include "Warehouse.h"

void Warehouse::Put(std::string name) {
	products.push_back(name);
	StorageSpace::size--;
}
Warehouse::Warehouse(int s) : StorageSpace{ s } {}