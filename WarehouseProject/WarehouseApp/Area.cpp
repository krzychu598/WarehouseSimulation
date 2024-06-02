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


void Area::put(const nlohmann::json& box) {
	occupied_space_size++;
	//TODO calculate priority, check shelving empty size, change this code later
	shelvings[0]->put(box);
}
//TODO najpierw sprawdza priority A -> B -> C
bool Area::find(std::string name, int amount) const {
	for (auto& shelving : shelvings) {
		if(shelving->find(name, amount) == true){
			return true;
		}
	}
	return false;
}



/*
auto it = std::find(products.begin(), products.end(), name);
if (it != products.end()) {
	PRINT_MSG("object ", name, " found");
	return true;
}
else {
	PRINT_MSG("object ", name, " not found");
	return false;
}
*/