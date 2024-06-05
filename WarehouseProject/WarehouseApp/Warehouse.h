#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <unordered_map>
#include <time.h>
#include <chrono>
#include <thread>
#include "nlohmann/json.hpp"
#include "DebugMacros.h"
#include "StorageSpace.h"
#include "Area.h"
#include "Box.h"
#include "Product.h"
#include "Employee.h"
constexpr auto FOLDER = "../SharedJsons/";
class Warehouse :
    public StorageSpace
{
public:
    Warehouse(const std::string& file_path);
    ~Warehouse();
    void put(const nlohmann::json& box);
    bool find(std::string name, int amount = 1, std::string type = "undefined") const;
    std::unique_ptr<Product> get(std::string&& name, std::string type); //r-value reference
    bool reviewDelivery(const std::string& file_path);
    bool reviewRequest(const std::string& file_path);
    void acceptDelivery(const std::string& file_path);
    void sendDelivery(const std::string& file_path);
    void startWorking(const std::vector<std::string>& deliveries, const std::vector<std::string>& requests);
    void assignToJob(const std::string& work_type, unsigned int work_load);
private:
    nlohmann::json getJsonData(const std::string& file_path) {
        std::ifstream f(file_path);
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
    }
    std::unordered_map<std::string, std::vector<Employee>> work_types;  //employees segregated based on work type
    std::vector<std::unique_ptr<Area>> areas;
    std::string name;
};