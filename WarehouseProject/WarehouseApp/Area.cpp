#include "Area.h"

Area::Area(const nlohmann::json& area) : type(area["type"]) {
	size = area["size"];
	for (const auto& shelving : area["shelvings"]) {
		shelvings.push_back(std::make_unique<Shelving>(shelving));
	}
	PRINT_MSG("Area ", type, " created");
};

Area::~Area() { PRINT_MSG("Area ", type, " destroyed"); };

std::string Area::getType() const {	return type; };


void Area::put(std::string name) {
	products.push_back(name);
}

bool Area::find(std::string name) const {
	auto it = std::find(products.begin(), products.end(), name);
	if (it != products.end()) {
		PRINT_MSG("object ", name, " found");
		return true;
	}
	else {
		PRINT_MSG("object ", name, " not found");
		return false;
	}
}