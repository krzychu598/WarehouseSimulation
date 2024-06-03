#pragma once
#include <iostream>
#include <vector>
#include "Product.h"

class StorageSpace
{
public:
	virtual Product take(Product& product);

	bool find(std::string name, int amount=1) const;
	bool find(int id, int amount = 1) const;
	bool find(Product product, int amount = 1) const;
	virtual unsigned int getEmptySpace() const;
	virtual unsigned int getOccupiedSpace() const;
	virtual unsigned int getFullSpace() const;


protected:
	StorageSpace();
	virtual ~StorageSpace();
	unsigned int size;
	unsigned int occupied_space_size;
};

