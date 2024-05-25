#pragma once
#include <string>
#include <iostream>

#include "nlohmann/json.hpp"

#include "StorageSpace.h"
#include "Shelving.h"

class Area :
    public StorageSpace
{
public:
    Area(std::string& type, nlohmann::json shelvings);
    std::string getType() const;
    void put(std::string name);
    bool find(std::string name) const;

    //to delete later
    std::vector<std::string> products;
private:
    std::string type;
    std::vector<std::unique_ptr<Shelving>> shelvings;

};

