#include "StorageSpace.h"

StorageSpace::StorageSpace() : size(0), occupied_space_size(0){};
StorageSpace::~StorageSpace() {};
Product StorageSpace::take(Product& product) { return Product("none"); };
bool StorageSpace::find(std::string name, int amount) const { return false; };
bool StorageSpace::find(int id, int amount) const { return false; };
bool StorageSpace::find(Product product, int amount) const { return false; };
unsigned int StorageSpace::getEmptySpace() const { return size - occupied_space_size; };
unsigned int StorageSpace::getOccupiedSpace() const { return occupied_space_size; };
unsigned int StorageSpace::getFullSpace() const { return size; };


