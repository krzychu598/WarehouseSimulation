#pragma once
#include "StorageSpace.h"
#include "nlohmann/json.hpp"
#include "Product.h"
#include <iostream>
#include "DebugMacros.h"

class Box :
    public StorageSpace
{
public:
    Box(const nlohmann::json& box);
    void put(Product& product);
    unsigned int getProductAmount() const;
    unsigned int getEmptySpace() const;
    unsigned int getOccupiedSpace() const;
    void updateOccupiedSpace();
    std::string getType() const;
private:
    std::vector<std::unique_ptr<Product>> products;
    std::string product_name;
};

