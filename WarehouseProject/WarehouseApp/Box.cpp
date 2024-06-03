#include "Box.h"
Box::Box(const nlohmann::json& box) : product_name(box.at("product_name")) {
	size = 360;
	occupied_space_size = 0;
	for (unsigned int i = 0; i < box["product_count"].get<unsigned int>(); ++i) {
		products.push_back(std::make_unique<Product>(box));
	};
	this->updateOccupiedSpace();
	this->updateFullPrice();
	type = products[0]->getType();
	PRINT_MSG("put ", box.at("product_name"), " box");
};
Box::Box(){
	size = 360;
};
void Box::put(std::unique_ptr<Product> product) {

	products.push_back(std::move(product));
	this->updateOccupiedSpace();
	
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
std::unique_ptr<Product> Box::get(std::string& name)
{	//works only for boxes sitting in storage.(doesn't work for outgoing delivery boxes)
	for (auto& product : products)
	{	

		if (product->getName() == name) {
			auto ptr = std::move(products.back());
			products.pop_back();
			return ptr;
		};
	}
};
unsigned int Box::getProductAmount() const { return products.size(); };
unsigned int Box::getProductAmount(std::string& name) const {
	unsigned int amount = 0;
	for (auto& product : products) {
		if (product->getName() == name) {
			amount++;
		}
	}
	return amount;
};

void Box::updateOccupiedSpace() 
{
	unsigned int new_space = 0;
	for (const auto& product : products)
	{
		new_space += product->getSize();
	}
	occupied_space = new_space;
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
std::string Box::getType() const { return type; };
std::string Box::getProductName() const { return product_name; };