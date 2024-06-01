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
    bool find(std::string name) const;
    std::unique_ptr<Product> getProduct(std::string name) const; //this method does essantialy the same thing as find but returns the product instead of bool. Don't know if this is right.
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

