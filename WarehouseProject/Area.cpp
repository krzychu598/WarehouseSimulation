#include "Area.h"

Area::Area(std::string& type, nlohmann::json shelvings) : type(type) {};

std::string Area::getType() const {
	return type;
};

void Area::put(std::string name) {
	products.push_back(name);
}

bool Area::find(std::string name) const {
	auto it = std::find(products.begin(), products.end(), name);
	if (it != products.end()) {
		return true;
	}
	else {
		return false;
	}
}
