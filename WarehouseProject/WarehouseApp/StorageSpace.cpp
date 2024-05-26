#include "StorageSpace.h"

StorageSpace::StorageSpace() {

}
int StorageSpace::getSize() const {
	return size;
}

Product StorageSpace::take(Product& product) { return Product("none"); };
void StorageSpace::put(Product& product) {};
bool StorageSpace::find(std::string name, int amount) const { return false; };
bool StorageSpace::find(int id, int amount) const { return false; };
bool StorageSpace::find(Product product, int amount) const { return false; };
unsigned int StorageSpace::getEmptySpace() const { return 0; };
unsigned int StorageSpace::getFullSpace() const { return 0; };

