#include "Shelving.h"
#include <variant>

Shelving::Shelving(const nlohmann::json& shelving){
	size = shelving["size"].get<int>();
	priority = priority_map.at(shelving["priority"].get<std::string>()[0]); /*Take priority from json structure.It is string.
	Now take first character from this string("A"[0] = 'A' - conversion from string to char)
	Then using unordered map get corresponding enum class instance
	*/
};

void Shelving::put(const nlohmann::json& box) {
	boxes.push_back(std::make_unique<Box>(box));
	
};

bool Shelving::find(std::string& name, int amount) const{
	for (const auto& box : boxes) {
		unsigned int curr_amount = 0;
		if (box->find(name) == true) {
			curr_amount += box->getProductAmount(name);
			if (curr_amount >= amount) {
				return true;
			}
		}

	}
	return false;
}

std::unique_ptr<Product> Shelving::get(std::string& name) {
	for (auto& box : boxes) {
		if (box->find(name) == true) {
			return std::move(box->get(name));
		}
	}
};
