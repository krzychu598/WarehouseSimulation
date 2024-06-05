#include "Employee.h"

Employee::Employee()
{
	name = "place_holder";
	id = 0;
	is_forklift_certified = false;
	experience = Experience::intern;
}
Employee::Employee(unsigned int p_id, bool p_is_forklift_certified) :id(p_id), is_forklift_certified(p_is_forklift_certified) {}

Employee::Employee(const nlohmann::json& info) {
	name = info["name"];
	id = info["id"].get<unsigned int>();
	is_forklift_certified = info["forklift"].get<bool>();
	//initiate experience
	experience = static_cast<Experience>(info["experience"]);
};

bool Employee::is_certified()
{
	return is_forklift_certified;
}
unsigned int Employee::getId()
{
	return id;
}
void Employee::setId(unsigned int new_id)
{
	id = new_id;
}
void Employee::setCertified(bool new_state)
{
	is_forklift_certified = new_state;
}
