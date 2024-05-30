#pragma once
#include <string>
#include <iostream>

#include "nlohmann/json.hpp"

#include "StorageSpace.h"
#include "Shelving.h"
#include "DebugMacros.h"

class Area :
    public StorageSpace
{
public:
    Area(const nlohmann::json& area);
    ~Area();
    std::string getType() const;
    void put(const nlohmann::json& box);
    bool find(std::string name) const;

    //to delete later
    std::vector<std::string> products;
private:
    std::string type;
    std::vector<std::unique_ptr<Shelving>> shelvings;

};

