#include "Box.h"

Box::Box()
{
	size = 360;
	occupied_space_size = 0;
	this->updateFullPrice();
};
void Box::put(std::unique_ptr<Product> product) 
{
	products.push_back(std::move(product));
	this->updateOccupiedSpace();
	this->updateFullPrice();
};

std::unique_ptr<Product> Box::get(std::string& name) {
	return nullptr;
};

bool Box::find(std::string& name) const 
{
	for (const auto& product : products) 
	{
		if (product->getName() == name) {
			return true;
		};
	}
	return false;
};
unsigned int Box::getProductAmount() const { return products.size(); };
void Box::updateOccupiedSpace() 
{
	unsigned int new_space = 0;
	for (const auto& product : products)
	{
		new_space += product->getSize();
	}
	occupied_space_size = new_space;
};
unsigned int Box::getFullPrice() const { return full_price; };
void Box::updateFullPrice()
{
	unsigned int new_price = 0;
	for (const auto& product : products)
	{
		new_price += product->getPrice();
	}
	full_price = new_price;
};