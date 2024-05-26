#pragma once
#include <iostream>
#include <vector>
#include "Product.h"

class StorageSpace
{
public:
	int getSize() const;
	virtual Product take(Product& product);
	virtual void put(Product& product);

	bool find(std::string name, int amount=1) const;
	bool find(int id, int amount = 1) const;
	bool find(Product product, int amount = 1) const;
	unsigned int getEmptySpace() const;
	unsigned int getFullSpace() const;


protected:
	StorageSpace();
	int size;
};

//Log: A Delivery phase 1.New delivery request, 2. Employees take products, 3. Employees place products, 4. Delivery is completed B relocation 1 checking if Boxes are in the right places 2 Relocating Boxes

