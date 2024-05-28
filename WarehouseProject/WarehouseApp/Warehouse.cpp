#include "Warehouse.h"

void Warehouse::put(std::string name, std::string type) {
	for (auto& area : areas) {
		if ((area)->getType() == type) {
			(area)->put(name);
			return;
		}
	}
	PRINT_MSG("Couldn't put ", name, "");
}

bool Warehouse::find(std::string name, std::string type) const {
	for (auto& area : areas) {
		if ((area)->getType() == type) {
			return (area)->find(name);
		}
	}
	PRINT_MSG("object ", name, " not found");
	return false;
}

void Warehouse::acceptDelivery(const std::string& file_path) {
	nlohmann::json delivery_json;
	delivery_json = getJsonData(file_path);

	if (delivery_json["size"].get<int>() > size - occupied_space_size) {
		std::cout << "Delivery doesn't fit in the Warehouse\n";
		return;
	}
	for (const auto& box : delivery_json.at("boxes")) {
		this->put(box.at("product_name"), box.at("type"));
	}


};
Warehouse::Warehouse(const std::string& file_path) : StorageSpace() {
	json_data = getJsonData(file_path);

	name = json_data.at("name");
	size = json_data.at("size").get<unsigned int>();

	for (const auto& area_json : json_data["areas"]) {
		areas.push_back(std::make_unique<Area>(
			area_json
		));
	}
	PRINT_MSG("Warehouse ", name, " created");
}

Warehouse::~Warehouse() {
	PRINT_MSG("Warehouse ", name, " destroyed");
}
