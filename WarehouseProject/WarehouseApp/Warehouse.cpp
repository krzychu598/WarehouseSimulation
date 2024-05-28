#include "Warehouse.h"

void Warehouse::put(std::string name, std::string type) {
	for (auto& area : areas) {
		if ((area)->getType() == type) {
			(area)->put(name);
			return;
		}
	}
	std::cout << "No appriopiate area type!";

}

bool Warehouse::find(std::string name, std::string type) const {
	for (auto& area : areas) {
		if ((area)->getType() == type) {
			return (area)->find(name);
		}
	}
	return false;
}

void Warehouse::acceptDelivery(const std::string& file_path) {
	nlohmann::json delivery_json;
	delivery_json = getJsonData(file_path);

};
Warehouse::Warehouse(const std::string& file_path) : StorageSpace() {
	//load data from file
	json_data = getJsonData(file_path);

	name = json_data["name"].get<std::string>();
	for (const auto& area_json : json_data["areas"]) {
		std::string type = area_json["type"].get<std::string>();
		areas.push_back(std::make_unique<Area>(
			type,
			area_json["shelvings"]
		));
	}
	PRINT_MSG("Warehouse ", name, " created");
}

Warehouse::~Warehouse() {
	PRINT_MSG("Warehouse ", name, " destroyed");
}
