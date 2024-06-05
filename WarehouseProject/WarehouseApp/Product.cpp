#include "Product.h"
Product::Product(std::string name, unsigned int size, unsigned int price, std::string type)
	: name(name), size(size), price(price), type(type) {};
Product::Product()
{
	name = "Undefined";
	size = 0;
	price = 0;
	type = "Undefined";
}

Product::Product(const nlohmann::json& info) {
	type = info["type"];
	kind = info["kind"];
	name = info["product_name"];
	manufacturer_name = info["manufacturer_name"];
	size = info["size"];
	price = info["price"];


}
void Product::setName(std::string new_name)
{
	name = new_name;
}
void Product::setPriority(unsigned int new_priority)
{
	priority = new_priority;
}
void Product::setSize(unsigned int new_size)
{
	size = new_size;
}
std::string Product::getName() const
{
	return name;
}
unsigned int Product::getSize() const
{
	return size;
}
unsigned int Product::getPriority() const
{
	return priority;
}
unsigned int Product::getPrice() const { return price; };
std::string Product::getType() const { return type; };
std::string Product::getKind() const { return kind; };