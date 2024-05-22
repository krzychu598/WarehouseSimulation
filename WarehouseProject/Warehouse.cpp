#include "Warehouse.h"

using json = nlohmann::json;

void Warehouse::put(std::string name) {
	products.push_back(name);
	StorageSpace::size--;
}
Warehouse::Warehouse(const std::string& file_path) : StorageSpace() {
	//load data from file
	std::ifstream f(file_path);

	if (!f.is_open()) {
		throw std::exception("Couldn't open the file");
	}
	
	json data = json::parse(f);
	f.close();

	name = data["name"].get<std::string>();
	for (const auto& area_json : data["areas"]) {
		areas.push_back(std::make_unique<Area>(
			area_json["type"].get<std::string>(),
			area_json["shelvings"]
		));
	}
}