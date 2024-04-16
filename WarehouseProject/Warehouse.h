#pragma once
#include "StorageSpace.h"
#include <iostream>
#include <vector>
#include <string>

class Warehouse :
    public StorageSpace
{
public:
    Warehouse(int s);
    void Put(std::string name);
    std::vector<std::string> products;
};

