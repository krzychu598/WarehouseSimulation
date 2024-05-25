#pragma once
#include <iostream>
#include <vector>
#include "Product.h"

class StorageSpace
{
public:
	int getSize() const;
	//virtual Product Take(Product& product);
	//virtual void Put(Product& product);
	//bool Find(std::string name, int amount=1) const;
	//bool Find(int id, int amount = 1) const;
	//bool Find(Product product, int amount = 1) const;
	//unsigned int GetEmptySpace() const;
	//unsigned int GetFullSpace() const;


protected:
	StorageSpace();
	int size;
};

//Log: A Delivery phase 1.New delivery request, 2. Employees take products, 3. Employees place products, 4. Delivery is completed B relocation 1 checking if Boxes are in the right places 2 Relocating Boxes

