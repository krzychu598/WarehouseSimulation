#include "InBox.h"

InBox::InBox(const nlohmann::json& box) : product_name(box.at("product_name")) {
	size = 360;
	occupied_space_size = 360;
	for (unsigned int i = 0; i < box["product_count"].get<unsigned int>(); ++i) {
		products.push_back(std::make_unique<Product>(box));
	};
	priority = 0;
	this->updateOccupiedSpace();
	this->updateFullPrice();
	type = box.at("type");
	kind = box.at("kind");
	PRINT_MSG("put ", box.at("product_name"), " box");
};
InBox::~InBox() {};
void InBox::put(std::unique_ptr<Product> product) 
{
	if (product->getName() == product_name)
	{
		products.push_back(std::move(product));
		this->updateOccupiedSpace();
		this->updateFullPrice();
	}
	else { PRINT_MSG("Couldn't put: ", product->getName(), ""); } //Don't know if this is needed, as warehouse also prints a message when failed put
};
std::unique_ptr<Product> InBox::get()
{
			auto ptr = std::move(products.back());
			products.pop_back();
			this->updateOccupiedSpace();
			this->updateFullPrice();
			if (occupied_space_size == 0) { this->~InBox(); }
			return ptr;
};
std::string InBox::getType() const { return type; };
std::string InBox::getKind() const { return kind; };
std::string InBox::getProductName() const { return product_name; };
unsigned int InBox::getPriority() const { return priority; }