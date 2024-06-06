#include "Delivery.h"


using json = nlohmann::json;
Delivery::Delivery(std::vector<std::string> types) { 
	box_id = 178650;	//initial id
	srand(time(NULL));	//generate seed
	json data;
	for (auto& type : types) {
		type += ".json";
		data = getFromJson(type);
		initiateProducts(data);
	}
};

void Delivery::createDelivery(int size, const std::string& output_path, std::string type1, std::string type2, std::string type3) {
	json data;
	int type1_num = size;
	int type2_num = 0;
	int type3_num = 0;
	if (type3 != "") {
		type1_num = ((rand() % 30 + 30) * size) / 100;	//rand number beetween 0.30 size and 0.59 size
		type2_num = ((rand() % 20 + 20) * size) / 100 - type1_num;	//rand number between 0.2 size and 0.39 size
		type3_num = size - type1_num - type2_num;
	}
	if (type2 != "" && type3 =="") {
		type1_num = ((rand()%30 +50) * size) / 100;	//rand number beetween 0.50 size and 0.79 size
		type2_num = size - type1_num;
	}

	data["size"] = { {"size", size}, { type1, type1_num } };
	if (type2_num != 0) { data["size"][type2] = type2_num; }
	if (type3_num != 0) { data["size"][type3] = type3_num; }
	std::vector<json> type1_data = getBoxes(type1, type1_num);
	std::vector<json> type2_data = getBoxes(type2, type2_num);
	std::vector<json> type3_data = getBoxes(type3, type3_num);
	type1_data.insert(type1_data.end(), type2_data.begin(), type2_data.end()); //add two vectors together
	type1_data.insert(type1_data.end(), type3_data.begin(), type3_data.end());
	data["boxes"] = type1_data;
	dumpToFile(data, output_path);
	PRINT("created new delivery");


};

void Delivery::createRequest(int size, const std::string& output_path, std::string type){
	json data;
	data["type"] = type;
	std::vector<json> products;
	while (size != 0) {
		Kind& kind = choiceWeightedKind(type);
		products.push_back(createProduct(kind));
		size--;
			
	}
	data["products"] = products;
	dumpToFile(data, output_path);
	PRINT("created new request");
	};

void Delivery::updateDemand(Product& product) {
	
	//supply < demand
	if (product.supply <= product.demand) {
		product.demand+=RATIO;
	}
	//price is low
	if (product.avg_price <= ((product.max_price - product.min_price) / 2 + product.min_price)) {
		product.demand++;
	}
	product.demand = std::min(MAX_DEMAND, product.demand);
}

void Delivery::setTrend() {
	//a kind of product will be more likely to be chosen
	int random = rand() % types.size();
	int add = rand() % 10;
	for (auto& type : types) {
		if(random == 0){
			random = rand() % type.second.size();
			type.second[random].kind_demand += add * TREND_DIFF;
			PRINT_V("Set new trend ", type.second[random].name);

				break;
		}
		random--;

	}
}
void Delivery::showSupplyDemand() {
	for (auto& type : types) {
		for (auto& kind : type.second) {
			for (auto& product : kind.products) {
				PRINT_S(product.name, product.supply, product.demand);

			}
		}
	}
};

Delivery::Product::Product(const std::string& name, const std::string& man_name, int min_price, int max_price) :
	name(name), manufacturer_name(man_name), min_price(min_price), max_price(max_price) {
		supply = 0;
		int demand_type = rand() % 3;
		int add;
		switch (demand_type) {
		case 0:
			add = 0;
			break;
		case 1:
			add = 30;
			break;
		case 2:
			add = 60;
		}
		demand = rand() % 100 +add;
		avg_price = min_price;
	}
