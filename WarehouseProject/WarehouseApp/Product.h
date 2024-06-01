#pragma once
#include <iostream>
class Product
{
public:
	Product();
	Product(std::string name, unsigned int priority, unsigne dint size);
	void setName(std::string new_name);
	void setPriority(unsigned int new_priority);
	void setSize(unsigned int new_size);
	std::string getName();
	unsigned int getSize();
	unsigned int getPriority();
private:
	std::string name;
	unsigned int priority;
	unsigned int size;
};


