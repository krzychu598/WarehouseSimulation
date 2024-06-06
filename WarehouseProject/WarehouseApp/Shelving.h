//Maksymilian Zieliński
#pragma once
#include <unordered_map>
#include <vector>
#include "nlohmann/json.hpp"
#include "StorageSpace.h"
#include "InBox.h"
//TODO consider changing boxes to list (for now erasing boxes is inefficient)
class Shelving :
    public StorageSpace
{
public:
    Shelving(const nlohmann::json& shelving);
    void put(const nlohmann::json& box);
    void put(std::unique_ptr<InBox> box);
    bool find(std::string& name, unsigned int amount=1) const;
    bool isEmpty() const;
    std::unique_ptr<Product> get(std::string& name);
    std::unique_ptr<InBox> takeOutBox();
    unsigned int getPriority() const;
private:
    std::vector<std::unique_ptr<InBox>> boxes;
    enum class Priority { A, B, C };
    std::unordered_map<char, Priority> priority_map = {
        {'A', Priority::A},
        {'B', Priority::B},
        {'C', Priority::C}
    };
    Priority priority;

};

