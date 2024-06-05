#include "Shelving.h"
#include <variant>

Shelving::Shelving(const nlohmann::json& shelving){
	size = shelving["size"].get<int>();
	priority = priority_map.at(shelving["priority"].get<std::string>()[0]); 
	/*Take priority from json structure.It is string.
	Now take first character from this string("A"[0] = 'A' - conversion from string to char)
	Then using unordered map get corresponding enum class instance
	*/
};

void Shelving::put(const nlohmann::json& box) {
	boxes.push_back(std::make_unique<InBox>(box));
	occupied_space_size++;
	
};

bool Shelving::find(std::string& name, unsigned int amount) const{
	for (const auto& box : boxes) {
		unsigned int curr_amount = 0;
		if (box->find(name) == true) {
			curr_amount += box->getProductAmount();
			if (curr_amount >= amount) {
				return true;
			}
		}

	}
	return false;
}

std::unique_ptr<Product> Shelving::get(std::string& name) {
	std::unique_ptr<Product> ptr;
	bool to_delete = false;
	for (auto& box : boxes) {
		if (box->getProductName() == name) {
			ptr = std::move(box->get());
			if (box->getOccupiedSpace() == 0) { to_delete = true; }
			break;
			
		}
	}
	if (to_delete) {
		for (auto it = begin(boxes); it != end(boxes); ++it) {
			if ((*it)->getOccupiedSpace() == 0) {
				boxes.erase(it);
				occupied_space_size--;
				break;
			}
		}
	}
	return ptr;
};
