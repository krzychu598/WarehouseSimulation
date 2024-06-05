#pragma once
#include <iostream>
#include <vector>
#include "Product.h"

class StorageSpace
{
public:
	virtual Product take(Product& product);
	unsigned int getEmptySpace() const;
	unsigned int getOccupiedSpace() const;
	unsigned int getFullSpace() const;
protected:
	StorageSpace();
	virtual ~StorageSpace();
	unsigned int size;
	unsigned int occupied_space_size;
};

