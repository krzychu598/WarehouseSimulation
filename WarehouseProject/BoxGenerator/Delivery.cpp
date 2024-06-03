#include "Delivery.h"
constexpr auto BOX_SIZE = 360;

using json = nlohmann::json;
Delivery::Delivery() {};

nlohmann::json Delivery::createBox(const json& product_dict, std::string& type) {
	json dict;
	dict["type"] = type;
	dict["product_type_name"] = product_dict["product_name"];
	//TODO choose product based on trend. For now just take first element
	for (auto& el : product_dict["names_manufacturers"][0].items()) {
		dict["product_name"] = el.key();
		dict["manufacturer_name"] = el.value();
	}
	//for now fixed values. Implement rand or baseed on trend setting later
	dict["id"] = 0;
	dict["price"] = product_dict["min_price"];
	dict["size"] = product_dict["size"];
	dict["product_count"] = BOX_SIZE / product_dict["size"];
	if (BOX_SIZE % product_dict["size"] != 0) { throw std::runtime_error("Invalid size"); }
	return dict;
};

std::vector<json> Delivery::getBoxes(std::string& type, int num) {
	std::vector<json> boxes;
	if (num == 0) {
		return boxes;
	}
	std::string input = type + ".json";
	nlohmann::json products = getFromJson(input)["products"];
	while (num > 0) {
		boxes.push_back(createBox(products[num], type));
		num--;
	}
	return boxes;

};

void Delivery::createDelivery(int size, std::string type1, std::string type2, const std::string& output_path) {
	json data;
	int type1_num = size;
	int type2_num = 0;
	if (type2 != type1) {
		type1_num = 0.75 * size;
		type2_num = size - type1_num;
	}

	data["size"] = { {"size", type1_num}, { type1, type1_num } };
	if (type2_num != 0) { data["size"][type2] = type2_num; }

	std::vector<json> type1_data = getBoxes(type1, type1_num);
	std::vector<json> type2_data = getBoxes(type2, type2_num);
	type1_data.insert(type1_data.end(), type2_data.begin(), type2_data.end());
	data["products"] = type1_data;
	dumpToFile(data, output_path);
};

nlohmann::json Delivery::createProduct(const json& in_data, std::string& type) {
	json dict;
	dict["type"] = type;
	dict["product_type_name"] = in_data["product_name"];
	for (auto& el : in_data["names_manufacturers"][0].items()) {
		dict["product_name"] = el.key();
	}
	dict["quantity"] = 1;
	return dict;
	};

void Delivery::createRequest(int num, std::string type, const std::string& output_path){
	json data;
	std::vector<json> products;

	std::string input = type + ".json";
	json in_data = getFromJson(input)["products"][0];
	while (num != 0) {
		products.push_back(createProduct(in_data, type));
		num--;
			
	}
	data["products"] = products;
	dumpToFile(data, output_path);
	};

