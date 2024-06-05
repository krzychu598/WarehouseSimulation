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
	//shelvings filled in order they were initialized A->B->C
	for (auto& shelving : shelvings) {
		if (shelving->getEmptySpace()) {
			shelving->put(box);
			break;
		}
	}

}
bool Area::find(std::string name, int amount) const {
	for (auto& shelving : shelvings) {
		if(shelving->find(name, amount) == true){
			return true;
		}
	}
	return false;
}

std::unique_ptr<Product> Area::get(std::string& name) {
	for (auto& shelving : shelvings) {
		if (shelving->find(name) == true) {
			return std::move(shelving->get(name));
		}
	}
};