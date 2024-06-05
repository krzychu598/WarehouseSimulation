#include "StorageSpace.h"

StorageSpace::StorageSpace() : size(0), occupied_space_size(0){};
StorageSpace::~StorageSpace() {};
Product StorageSpace::take(Product& product) { return Product("none"); };
unsigned int StorageSpace::getEmptySpace() const { return size - occupied_space_size; };
unsigned int StorageSpace::getOccupiedSpace() const { return occupied_space_size; };
unsigned int StorageSpace::getFullSpace() const { return size; };


