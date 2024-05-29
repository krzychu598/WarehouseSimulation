#include "Box.h"

Box::Box(const nlohmann::json& box) {};
void Box::put(Product& product) {};
unsigned int Box::getProductAmount() const {};
unsigned int Box::getEmptySpace() const {};
unsigned int Box::getOccupiedSpace() const {};
void Box::updateOccupiedSpace() {};