#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "nlohmann/json.hpp"
//#include "Trend.h"
class Delivery {
public:
    Delivery();
    
    nlohmann::json createBox(const nlohmann::json& product_dict, std::string& type);
    std::vector<nlohmann::json> getBoxes(std::string& type, int num);
    void createDelivery(int size, std::string type1, std::string type2, const std::string& output_path="delivery.json");

    nlohmann::json createProduct(const nlohmann::json& data, std::string& type);
    void createRequest(int num, std::string type, const std::string& output_path = "request.json");
private:
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

    void dumpToFile(const nlohmann::json& data, const std::string& output_path) {
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

