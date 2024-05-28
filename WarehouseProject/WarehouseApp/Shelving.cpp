#include "Shelving.h"

Shelving::Shelving(const nlohmann::json& shelving){
	size = shelving["size"].get<int>();
	priority = priority_map.at(shelving["priority"].get<std::string>()[0]); /*Take priority from json structure.It is string.
	Now take first character from this string("A"[0] = 'A' - conversion from string to char)
	Then using unordered map get corresponding enum class instance
	*/
};

void Shelving::put(std::string name) {};