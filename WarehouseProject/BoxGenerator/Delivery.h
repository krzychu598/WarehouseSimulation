#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "nlohmann/json.hpp"
//#include "Trend.h"

constexpr auto BOX_SIZE = 360;

class Delivery {
public:
    Delivery();
    
    void createDelivery(int size, std::string type1, std::string type2, const std::string& output_path="delivery.json");
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

    void dumpToFile(const nlohmann::json& data, const std::string& file_name) {
        std::string output_path = "../SharedJsons/" + file_name;
        std::ofstream f(output_path);
        if (!f.is_open()) {
            throw std::runtime_error("Couldn't open the file");
        }

        try {
            f << std::setw(4) <<  data;
        }
        catch (...) {
            throw std::runtime_error("cannot transfer data to file");
        }

        f.close();
    };

    nlohmann::json createBox(const nlohmann::json& product_dict, std::string& type) {
        nlohmann::json dict;
        dict["type"] = type;
        dict["product_type_name"] = product_dict["product_name"];
        //TODO choose product based on trend. For now just take first element
        for (auto& sub : product_dict["names_manufacturers"]) {
            for (auto el : sub.items()) {
                dict["product_name"] = el.key();
                dict["manufacturer_name"] = el.value();
                break;
            }
            break;
        }
        //for now fixed values. Implement rand or baseed on trend setting later
        dict["id"] = 0;
        dict["price"] = product_dict["min_price"];
        dict["size"] = product_dict["size"];
        dict["product_count"] = BOX_SIZE / product_dict["size"];
        if (BOX_SIZE % product_dict["size"] != 0) { throw std::runtime_error("Invalid size"); }
        return dict;
    };

    std::vector<nlohmann::json> getBoxes(std::string& type, int num) {
        std::vector<nlohmann::json> boxes;
        if (num == 0) {
            return boxes;
        }
        std::string input = type + ".json";
        nlohmann::json products = getFromJson(input)["products"];
        nlohmann::json product;
        for (auto& sub : products) {
            product = sub;
            break;
        }
        while (num > 0) {
            boxes.push_back(createBox(product, type));
            num--;
        }
        return boxes;

    };

    nlohmann::json createProduct(const nlohmann::json& in_data, std::string& type) {
        nlohmann::json dict;
        dict["type"] = type;
        dict["product_type_name"] = in_data["product_name"];
        for (auto& sub : in_data["names_manufacturers"]) {
            for (auto el : sub.items()) {
                dict["product_name"] = el.key();
                break;
            }
            break;
        }
        dict["quantity"] = 1;
        return dict;
    };
};

