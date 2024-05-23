#pragma once
#include "StorageSpace.h"
#include "Area.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include "include/nlohmann/json.hpp"

class Warehouse :
    public StorageSpace
{
public:
    Warehouse(const std::string& file_path);
    void put(std::string name);
    std::vector<std::string> products;
private:
    std::vector<std::unique_ptr<Area>> areas;
};

