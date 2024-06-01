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
    unsigned int getOccupiedSpace() const;
    void updateOccupiedSpace();
    unsigned int getFullPrice() const;
    void updateFullPrice();
    std::string getType() const;
    std::string getProductName() const;

private:
    std::vector<std::unique_ptr<Product>> products;
    std::string product_name;
    std::string type;
    unsigned int occupied_space;
    unsigned int full_price;
};

