#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "nlohmann/json.hpp"
#ifdef _DEBUG
#define PRINT(msg) std::cout << msg << "\n"
#else
#define PRINT(msg)
#endif

constexpr auto BOX_SIZE = 360;
constexpr auto TREND_DIFF = 50;
constexpr auto MAX_DEMAND = 1000;
constexpr auto RATIO = 10;
constexpr auto FOLDER = "../SharedJsons/";
class Delivery {
public:
    Delivery(std::vector<std::string> types);
    
    void createDelivery(int size, const std::string& output_path, std::string type1, std::string type2="", std::string type3="");
    void createRequest(int size, const std::string& output_path, std::string type );
    void setTrend();
    struct Product {
        Product(const std::string& name, const std::string& man_name, int min_price, int max_price);
        std::string name;
        std::string manufacturer_name;
        int supply;
        int demand;
        int avg_price;
        int min_price;
        int max_price;
    };
    void updateDemand(Product& product);

private:
    inline static int box_id;

    struct Kind {
        Kind(std::string kind_name, std::vector<Product> products, int size) : name(kind_name), products(products), size(size) { kind_demand = 100; };
        std::string name;
        std::vector<Product> products;
        int size;
        int kind_demand;
    };
    std::unordered_map<std::string, std::vector<Kind>> types;



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
        std::string output_path = FOLDER + file_name;
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
    
    void initiateProducts(const nlohmann::json& data) {
        //create type
        std::vector<Kind> new_kinds;
        for (auto& kind : data["kinds"]) {
            //create Kind
            std::vector<Product> new_products;
            for (auto& product : kind["products"]) {
                //create product
                Product new_product(product["name"], product["manufacturer_name"], kind["min_price"], kind["max_price"]);
                new_products.push_back(new_product);
            }
            Kind new_kind(kind["name"].get<std::string>(), new_products, kind["size"].get<int>());
            new_kinds.push_back(new_kind);
        }
        types[data["type"]] = new_kinds;
    }

    Kind& choiceWeightedKind(const std::string& type) {
        if (types[type].size() == 0) { throw std::runtime_error("Invalid type"); }
        int importance_sum = 0;
        
        for (auto& kind : types[type]) {
            importance_sum += kind.kind_demand;
        }
        int random = rand() % importance_sum;

        for (auto& kind : types[type]) {
            importance_sum -= kind.kind_demand;
            if (importance_sum <= random) {
                return kind;
            }
        }
        throw std::runtime_error("Kind choice error");

    }
    Product& choiceWeightedProduct(Kind& kind) {
        int importance_sum = 0;

        for (auto& product : kind.products) {
            importance_sum += product.demand;
        }

        if (!importance_sum) { importance_sum = 1; }
        int random = rand() % importance_sum;

        for (auto& product : kind.products) {
            importance_sum -= product.demand;
            if (importance_sum <= random) {
                return product;
            }
        }
        throw std::runtime_error("Product choice error");

    }

    Product& choiceRandomProduct(Kind& kind) {
        int random = rand() % kind.products.size();
        return kind.products[random];
    }
    
    int choosePrice(Product& product) {
        //Also manages demand and supply
       
        //Price based on demand, min_price, max_price
        int half_between = (product.max_price - product.min_price);
        int price = rand() % (half_between);
        price += product.min_price;
        price += half_between * product.demand / MAX_DEMAND;

        //updates average_price based on supply
        product.avg_price = (product.avg_price * product.supply + price) / std::max(product.supply, 1);
        product.supply+=RATIO;
        updateDemand(product);
        return price;
    }
    
    nlohmann::json createBox(Kind& kind, const std::string& type) {
        nlohmann::json dict;
        dict["id"] = box_id;
        box_id++;
        dict["type"] = type;
        dict["kind"] = kind.name;
        dict["size"] = kind.size;
        dict["product_count"] = (BOX_SIZE / kind.size);
        if (BOX_SIZE % kind.size != 0) { throw std::runtime_error("Invalid size"); }

        Product& product = choiceWeightedProduct(kind);
        dict["product_name"] = product.name;
        dict["manufacturer_name"] = product.manufacturer_name;
        dict["price"] = choosePrice(product);

        return dict;
    };

    std::vector<nlohmann::json> getBoxes(const std::string& type, int num) {
        std::vector<nlohmann::json> boxes;
        if (num == 0) {
            return boxes;
        }
        while (num > 0) {
            Kind& kind = choiceWeightedKind(type);
            boxes.push_back(createBox(kind, type));
            num--;
        }
        return boxes;

    };

    nlohmann::json createProduct(Kind& kind) {
        nlohmann::json product_dict;
        product_dict["kind"] = kind.name;
        Product& product = choiceWeightedProduct(kind);
        product_dict["product_name"] = product.name;
        int quant = rand() % 3 + 1;
        product_dict["quantity"] = quant;

        //update supply
        product.supply = std::max(product.supply - quant, 0);

        return product_dict;
    };
};

