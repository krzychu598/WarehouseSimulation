#pragma once
#include <iostream>
#include "nlohmann/json.hpp"
class Product
{
public:
	Product();
	Product(std::string name, unsigned int size, unsigned int price, std::string type);
	Product(const nlohmann::json& info);
	void setName(std::string new_name);
	void setSize(unsigned int new_size);
	std::string getName() const;
	unsigned int getSize() const;
	unsigned int getPrice() const;
	std::string getType() const;
	std::string getKind() const;
private:
	std::string type;
	std::string kind;
	std::string name;
	std::string manufacturer_name;
	unsigned int size;
	unsigned int price;
};


