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

bool Warehouse::find(std::string name, int amount, std::string type) const {
	for (auto& area : areas) {

		if (type == "undefined") {
			if (!area->find(name,amount)) {
				continue;
			};
			PRINT_MSG("object ", name, " found");
			return true;

		}

		if (area->getType() == type) {
			bool result = area->find(name, amount);
			PRINT_MSG_N("object ", name, result, " found");
			return result;
		}
	}
	PRINT_MSG("object ", name, " not found");
	return false;
}

std::unique_ptr<Product> Warehouse::get(std::string& name, std::string type) {
	for (auto& area : areas) {

		if (area->getType() == type) {
			return std::move(area->get(name));
		}
	}
	PRINT_MSG("Couldn't get ", name, "");
};


void Warehouse::acceptDelivery(const std::string& file_path) {
	PRINT_MSG("\nInitializing delivery ", file_path, "");
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
	for (const auto& box : delivery_json["boxes"]) {
		this->put(box);
	};
};

void Warehouse::sendDelivery(const std::string& file_path) {
	PRINT_MSG("\nInitializing outgoing delivery ", file_path, "");
	nlohmann::json delivery_data = getJsonData(file_path);
	nlohmann::json products = delivery_data["products"];
	for (auto& product : products) {
		if (!this->find(product["product_name"], product["quantity"], product["type"])) {
			std::cout << "delivery cannot be sent. Not enough " << product["name"] << '\n';
			return;
			};
	};
	Box box;
	for (const auto& product : products) {
		std::string product_name = product["product_name"];
		box.put(std::move(this->get(product_name, product["type"])));
		PRINT_MSG("", product_name, " put in a delivery box");
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
	PRINT_MSG("\nWarehouse ", name, " destroyed");
}
