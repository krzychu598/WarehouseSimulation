#include "Warehouse.h"
#include <fstream>
using json = nlohmann::json;

void Warehouse::put(std::string name) {
	products.push_back(name);
	StorageSpace::size--;
}
Warehouse::Warehouse(const std::string& file_path) : StorageSpace() {
	//load data from file

	//pass arguments to area constructors


}