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
//TODO change this function (I changed it, I don't know if this should return bool or not, but my version doesn't work anyways)
std::variant<Product, bool> Shelving::find(std::string& name, std::string& type) const{ //not working because I'm on c++14 not 17
	for (const auto& box : boxes) {
		if (box->getType() == type) {
			if (box->find(name)) { return box->getProduct(name); }
		}
	}
	return false;
}