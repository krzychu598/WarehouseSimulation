#pragma once
#include "StorageSpace.h"
#include "Area.h"
#include "Box.h"
#include "Product.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include "nlohmann/json.hpp"
#include "DebugMacros.h"

class Warehouse :
    public StorageSpace
{
public:
    Warehouse(const std::string& file_path);
    ~Warehouse();
    void put(const nlohmann::json& box);
    bool find(std::string name, int amount = 1, std::string type = "undefined") const;
    void acceptDelivery(const std::string& file_path);
    void sendDelivery(const std::string file_path);
private:
    nlohmann::json getJsonData(const std::string& file_path) {
        std::ifstream f(file_path);

        if (!f.is_open()) {
            throw std::runtime_error("Couldn't open the file");
        }

        try {
            f >> Warehouse::json_data;
        }
        catch (...) {
            throw std::runtime_error("cannot transfer stream to json member");
        }

        f.close();
        return json_data;
    }
    std::vector<std::unique_ptr<Area>> areas;
    std::string name;
    nlohmann::json json_data;
};

//TODO Update json file, product should contain size, Box has const size 360