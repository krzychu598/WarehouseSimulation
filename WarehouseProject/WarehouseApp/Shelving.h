#pragma once
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "StorageSpace.h"
#include "Box.h"

class Shelving :
    public StorageSpace
{
public:
    Shelving(const nlohmann::json& shelving);
    void put(const nlohmann::json& box);
    bool find(std::string& name, std::string& type) const;
private:
    std::vector<std::unique_ptr<Box>> boxes;
    enum class Priority { A, B, C };
    std::unordered_map<char, Priority> priority_map = {
        {'A', Priority::A},
        {'B', Priority::B},
        {'C', Priority::C}
    };
    Priority priority;

};

