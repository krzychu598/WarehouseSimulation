#include "Delivery.h"


using json = nlohmann::json;
Delivery::Delivery() {};

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
	std::cout << data.dump(4) << '\n';
	std::vector<json> type1_data = getBoxes(type1, type1_num);
	std::vector<json> type2_data = getBoxes(type2, type2_num);
	type1_data.insert(type1_data.end(), type2_data.begin(), type2_data.end());
	data["boxes"] = type1_data;
	dumpToFile(data, output_path);
	std::cout << data.dump(4) << '\n';

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

