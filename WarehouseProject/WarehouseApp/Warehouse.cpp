#include "Warehouse.h"

void Warehouse::put(std::string name, std::string type) {
	for (auto& area : areas) {
		if ((area)->getType() == type) {
			(area)->put(name);
			break;
		}
	}

}

bool Warehouse::find(std::string name, std::string type) const {
	for (auto& area : areas) {
		if ((area)->getType() == type) {
			return (area)->find(name);
		}
	}
	return false;
}
Warehouse::Warehouse(const std::string& file_path) : StorageSpace() {
	//load data from file
	std::ifstream f(file_path);

	if (!f.is_open()) {
		throw std::runtime_error("Couldn't open the file");
	}

	try {
		f >> Warehouse::json_data;
	}
	catch (...) {
		throw std::runtime_error("cannot transfer stream to json member");
	}

	f.close();

	name = json_data["name"].get<std::string>();
	for (const auto& area_json : json_data["areas"]) {
		std::string type = area_json["type"].get<std::string>();
		areas.push_back(std::make_unique<Area>(
			type,
			area_json["shelvings"]
		));
	}
	PRINT_MSG("Warehouse created");
}

Warehouse::~Warehouse() {
	PRINT_MSG("Warehouse destroyed");
}
