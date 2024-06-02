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
    bool find(std::string name, int amount = 1) const;
private:
    std::string type;
    std::vector<std::unique_ptr<Shelving>> shelvings;

};

