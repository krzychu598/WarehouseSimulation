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
    Box();  //default constructor
    virtual void put(std::unique_ptr<Product> product);
    virtual std::unique_ptr<Product> get(std::string& name);

    bool find(std::string& name) const;
    unsigned int getProductAmount() const;
    void updateOccupiedSpace();
    unsigned int getFullPrice() const;
    void updateFullPrice();
protected:
    std::vector<std::unique_ptr<Product>> products;
    unsigned int full_price;
};

