#include "Delivery.h"


using json = nlohmann::json;
Delivery::Delivery() { id = 178650; srand(time(NULL)); };

void Delivery::createDelivery(int size, std::string type1, std::string type2, const std::string& output_path) {
	json data;
	int type1_num = size;
	int type2_num = 0;
	if (type2 != type1) {
		type1_num = ((rand()%50 +30) * size) / 100;	//rand number beetween 0.30 size and 0.79 size
		type2_num = size - type1_num;
	}

	data["size"] = { {"size", size}, { type1, type1_num } };
	if (type2_num != 0) { data["size"][type2] = type2_num; }
	std::vector<json> type1_data = getBoxes(type1, type1_num);
	std::vector<json> type2_data = getBoxes(type2, type2_num);
	type1_data.insert(type1_data.end(), type2_data.begin(), type2_data.end()); //add two vectors together
	data["boxes"] = type1_data;
	dumpToFile(data, output_path);
	//std::cout << data.dump(4) << '\n';

};

void Delivery::createRequest(int num, std::string type, const std::string& output_path){
	json data;
	std::vector<json> products;

	std::string input = type + ".json";
	json json_products = getFromJson(input)["products"];
	nlohmann::json product;
	while (num != 0) {
		product = choiceWeighted(json_products);
		products.push_back(createProduct(product, type));
		num--;
			
	}
	data["products"] = products;
	dumpToFile(data, output_path);
	};

void Delivery::updateDemand() {
	//supply < demand
	for (std::unordered_map<std::string, int>::iterator it = demand.begin(); it != demand.end(); ++it) {
		if (it->second >= supply[it->first]) {
			it->second++;
		}
	}
	//price < (max_price-min_price)/2

	//product type is in demand
}

void Delivery::setTrend() {
	if (demand.size() == 0) {
		return;
	}
	int random = rand() % demand.size();
	for (std::unordered_map<std::string, int>::iterator it = demand.begin(); it != demand.end(); ++it) {
		random--;
		if (random != 0) {
			continue;
		}
		it->second += 10;
		//std::cout << it->first << " is trending\n";
		break;
	}
}