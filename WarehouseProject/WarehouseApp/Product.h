#pragma once
#include <iostream>
#include "nlohmann/json.hpp"
class Product
{
public:
	Product();
	Product(std::string name, unsigned int priority, unsigned int size, unsigned int Price, std::string type);
	Product(const nlohmann::json& info);
	void setName(std::string new_name);
	void setPriority(unsigned int new_priority);
	void setSize(unsigned int new_size);
	std::string getName() const;
	unsigned int getSize() const;
	unsigned int getPriority() const;
	unsigned int getPrice() const;
	std::string getType() const;
private:
	std::string type;
	std::string kind;
	std::string name;
	std::string manufacturer_name;
	unsigned int priority;
	unsigned int size;
	unsigned int price;
};


