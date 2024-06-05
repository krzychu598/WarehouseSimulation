#include "InBox.h"

InBox::InBox(const nlohmann::json& box) : product_name(box.at("product_name")) {
	size = 360;
	occupied_space_size = 360;
	for (unsigned int i = 0; i < box["product_count"].get<unsigned int>(); ++i) {
		products.push_back(std::make_unique<Product>(box));
	};
	priority = priority_map.at(box["priority"].get<std::string>()[0]); //This might be wrong, can you check if it complies with the json structure?
	this->updateOccupiedSpace();
	this->updateFullPrice();
	type = products[0]->getType();
	kind = products[0]->getKind();
	PRINT_MSG("put ", box.at("product_name"), " box");
};
InBox::~InBox() {};
void InBox::put(std::unique_ptr<Product> product) 
{
	if (product->getName() == products[0]->getName())
	{
		products.push_back(std::move(product));
		this->updateOccupiedSpace();
		this->updateFullPrice();
	}
	else { PRINT_MSG("Couldn't put: ", product->getName(), ""); } //Don't know if this is needed, as warehouse also prints a message when failed put
};
std::unique_ptr<Product> InBox::get(std::string& name)
{
	for (auto& product : products)
	{

		if (product->getName() == name) {
			auto ptr = std::move(products.back());
			products.pop_back();
			this->updateOccupiedSpace();
			this->updateFullPrice();
			if (occupied_space_size == 0) { this->~InBox(); }
			return ptr;
		};
	}
};
std::string InBox::getType() const { return type; };
std::string InBox::getKind() const { return kind; };
std::string InBox::getProductName() const { return product_name; };