#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "nlohmann/json.hpp"
//#include "Trend.h"
class Delivery {
public:
    Delivery(std::string name="output");
    
    nlohmann::json createBox(const nlohmann::json& product_dict, std::string& type);
    std::vector<nlohmann::json> getBoxes(std::string& type, int num);
    void createDelivery(int size, std::string type1, std::string type2="");
private:
    std::string output_path;
    nlohmann::json getFromJson(const std::string& file_name) {
        std::ifstream f(file_name);
        nlohmann::json data;
        if (!f.is_open()) {
            throw std::runtime_error("Couldn't open the file");
        }

        try {
            f >> data;
        }
        catch (...) {
            throw std::runtime_error("cannot transfer stream to json member");
        }

        f.close();
        return data;
    };

    void dumpToFile(const nlohmann::json& data) {
        std::ofstream f(output_path);
        if (!f.is_open()) {
            throw std::runtime_error("Couldn't open the file");
        }

        try {
            f << data;
        }
        catch (...) {
            throw std::runtime_error("cannot transfer data to file");
        }

        f.close();
    };
};

