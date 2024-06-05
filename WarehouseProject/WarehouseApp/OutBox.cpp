#include "OutBox.h"

OutBox::OutBox()
{
	size = 360;
	occupied_space_size = 0;
	this->updateFullPrice();
};
unsigned int OutBox::getProductAmount(std::string& name) const
{
	unsigned int amount = 0;
	for (auto& product : products) {
		if (product->getName() == name) {
			amount++;
		}
	}
	return amount;
};