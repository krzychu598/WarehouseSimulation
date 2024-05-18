#pragma once
#include "StorageSpace.h"
class Box :
    public StorageSpace
{
public:
    std::vector<std::unique_ptr<Product>>& GetProducts()
};

