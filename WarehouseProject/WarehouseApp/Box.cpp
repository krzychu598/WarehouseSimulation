#include "Box.h"

Box::Box(const nlohmann::json& box) : product_name(box.at("product_name")) {
	size = 360;
	occupied_space_size = 360; //TODO calculate total size of products in box here, change json file so it includes product size
	for (unsigned int i = 0; i < box["product_count"].get<unsigned int>(); ++i) {
		products.push_back(std::make_unique<Product>(box["full_product_name"]));
	};
	PRINT_MSG("put ", box.at("product_name"), " box");
};
void Box::put(Product& product) {};
//TODO for now returns zero
unsigned int Box::getProductAmount() const { return 0; };
unsigned int Box::getEmptySpace() const { return 0; };
unsigned int Box::getOccupiedSpace() const { return 0; };
void Box::updateOccupiedSpace() {};
std::string Box::getType() const { return product_name; };