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
    unsigned int getExtraWorkLoad(const std::string& name, const std::string& type) const;
    std::unique_ptr<Product> get(std::string&& name, std::string type); //r-value reference
    bool find(std::string name, int amount = 1, std::string type = "undefined") const;
    bool reviewDelivery(const std::string& file_path);
    bool reviewRequest(const std::string& file_path);
    void put(const nlohmann::json& box);
    void acceptDelivery(const std::string& file_path, bool initial = false);
    void sendDelivery(const std::string& file_path);
    void startWorking(const std::vector<std::string>& deliveries, const std::vector<std::string>& requests);
    void updatePlacement();
    void employeeRest();
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
            std::cout << "Invalid file";
            return data;
        }

        f.close();
        return data;
    }
    struct Team {
        std::vector<Employee> employees;
        unsigned int full_work_capacity = 0;
        unsigned int current_work_capacity = 0;
        void addEmployee(Employee& employee) {
            employees.push_back(employee);
            full_work_capacity += 5 * employee.getExperience();
        }
        void rest() {
            current_work_capacity = full_work_capacity;
        }
    };
    std::unordered_map<std::string, Team> work_types;  //employees segregated based on work type
    std::vector<std::unique_ptr<Area>> areas;
    std::string name;
};