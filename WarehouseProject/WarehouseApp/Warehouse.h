#pragma once
#include "StorageSpace.h"
#include "Area.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include "nlohmann/json.hpp"

class Warehouse :
    public StorageSpace
{
public:
    Warehouse(const std::string& file_path);
    ~Warehouse();
    void put(std::string name, std::string type);
    bool find(std::string name, std::string type) const;
private:

    std::vector<std::unique_ptr<Area>> areas;
    std::string name;
    nlohmann::json json_data;
};
