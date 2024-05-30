#include "Warehouse.h"

void Warehouse::put(const nlohmann::json& box) {
	for (auto& area : areas) {
		if ((area)->getType() == box["type"]) {
			(area)->put(box);
			return;
		}
	}
	PRINT_MSG("Couldn't put: ", box["product_name"], "");
	PRINT_MSG("No appropiate area: ", box["type"], "");
}

bool Warehouse::find(std::string name, std::string type) const {
	for (auto& area : areas) {
		if ((area)->getType() == type) {
			bool result = area->find(name);
			PRINT_MSG_N("object ", name, result, " found");
			return result;
		}
	}
	PRINT_MSG("object ", name, " not found");
	return false;
}

void Warehouse::acceptDelivery(const std::string& file_path) {
	 
	nlohmann::json delivery_json = getJsonData(file_path);
	unsigned int delivery_size = delivery_json["size"]["size"].get<int>();
	if ( delivery_size > size - occupied_space_size) {
		std::cout << "Delivery doesn't fit in the Warehouse\n";
		return;
	}
	for (const auto& item : delivery_json["size"].items()) {
		
		for (const auto& area : areas) {

			if ((area)->getType() == item.key()) {
				if ((area)->getEmptySpace() < item.value()) {
					std::cout << "Delivery doesn't fit in the Warehouse\n";
					return;
				}
			};
		};
	};
	occupied_space_size += delivery_size;
	for (const auto& box : delivery_json.at("boxes")) {
		this->put(box);
	};
};

void Warehouse::reserveSpace(unsigned int reserved_size) {
	
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
