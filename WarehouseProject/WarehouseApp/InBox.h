#pragma once
#include "Box.h"
#include "nlohmann/json.hpp"
#include "Product.h"
#include <iostream>
#include "DebugMacros.h"

class InBox :
    public Box
{
public:
    InBox(const nlohmann::json& box);
    ~InBox();
    void put(std::unique_ptr<Product> product);
    std::unique_ptr<Product> get(std::string& name);
    std::string getType() const;
    std::string getKind() const;
    std::string getProductName() const;
private:
    std::string product_name;
    std::string type;
    std::string kind;
    enum class Priority { A, B, C };
    std::unordered_map<char, Priority> priority_map = {
        {'A', Priority::A},
        {'B', Priority::B},
        {'C', Priority::C}
    };
    Priority priority;
};