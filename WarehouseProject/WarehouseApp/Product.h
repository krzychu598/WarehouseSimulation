#pragma once
#include <iostream>
#include "nlohmann/json.hpp"
class Product
{
public:
	Product(std::string name);
private:
	std::string name;
};

