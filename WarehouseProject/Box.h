#pragma once
#include "StorageSpace.h"
#include <vector>

class Box :
    public StorageSpace
{
public:
    std::vector<std::unique_ptr<Product>>& GetProducts();
};

