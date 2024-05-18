#pragma once
#include <iostream>
#include <vector>
#include "Product.h"
#include "Box.h"

class StorageSpace
{
public:
	int GetSize() const;
	virtual Product Take(Product& product);
	virtual void Put(Product& product);
	bool Find(std::string name, int amount=1) const;
	bool Find(int id, int amount = 1) const;
	bool Find(Product product, int amount = 1) const;
	unsigned int GetEmptySpace() const;
	unsigned int GetFullSpace() const;
	

protected:
	StorageSpace(int size);
	int size;
};

//Log: A Delivery phase 1.New delivery request, 2. Employees take products, 3. Employees place products, 4. Delivery is completed B relocation 
