#pragma once
#include "StorageSpace.h"
#include "nlohmann/json.hpp"
#include "Product.h"

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
private:
    std::vector<std::unique_ptr<Product>> products;
    std::string product;
    unsigned int size = 360;
    unsigned int occupied_space_size;
    std::string type;
};

