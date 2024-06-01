#include "Product.h"
Product::Product(std::string name, unsigned int p_priority, int p_size) :name(name), priority(p_priority), size(p_size)
{}
Product::Product()
{
	name = "Undefined";
	priority = 0;
	size = 0;
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
std::string Product::getName()
{
	return name;
}
unsigned int Product::getSize()
{
	return size;
}
unsigned int Product::getPriority()
{
	return priority;
}

