#include "Area.h"

Area::Area(const nlohmann::json& area) : type(area["type"]) {
	size = area["size"];
	for (const auto& shelving : area["shelvings"]) {
		shelvings.push_back(std::make_unique<Shelving>(shelving));
	}
};

Area::~Area() { PRINT_MSG("Area ", type, " destroyed"); };

std::string Area::getType() const {	return type; };

void Area::updatePlacement() {
	// Collect all boxes and sort by priority
	std::vector<std::unique_ptr<InBox>> all_boxes;
	for (auto& shelving : shelvings) {
		while (!shelving->isEmpty()) {
			all_boxes.push_back(shelving->takeOutBox());
		}
	}

	std::sort(all_boxes.begin(), all_boxes.end(), [](const std::unique_ptr<InBox>& a, const std::unique_ptr<InBox>& b) {	//use of lambda function
		return a->getPriority() > b->getPriority();
		});

	for (auto& box : all_boxes) {
		for (auto& shelving : shelvings) {
			if (shelving->getEmptySpace()) {
				shelving->put(std::move(box));
				break;
			}
		}
	}
}

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

unsigned int Area::getExtraWorkLoad(std::string name) const {
	for (const auto& shelving : shelvings) {
		if (shelving->find(name)) {
			return shelving->getPriority();
		}
	}
	throw std::runtime_error("Box not found in any shelving");
};
