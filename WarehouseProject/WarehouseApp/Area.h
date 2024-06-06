//Krzysztof Wnorowski
#pragma once
#include <string>
#include <iostream>

#include "nlohmann/json.hpp"

#include "StorageSpace.h"
#include "Shelving.h"
#include "Product.h"
#include "DebugMacros.h"

class Area :
    public StorageSpace
{
public:
    Area(const nlohmann::json& area);
    ~Area();
    std::string getType() const;
    unsigned int getExtraWorkLoad(std::string name) const;
    void put(const nlohmann::json& box);
    void updatePlacement();
    bool find(std::string name, int amount = 1) const;
    std::unique_ptr<Product> get(std::string& name);
private:
    std::string type;
    std::vector<std::unique_ptr<Shelving>> shelvings;

};

