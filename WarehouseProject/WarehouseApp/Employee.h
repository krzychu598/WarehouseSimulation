#pragma once
#include "nlohmann/json.hpp"
class Employee
{
public:
	Employee();
	//const std::string& work_type
	Employee(unsigned int p_id, bool p_is_forklift_certified);
	Employee(const nlohmann::json& employee_info);
	unsigned int getId();
	bool is_certified();
	void setId(unsigned int new_id);
	void setCertified(bool new_c);

private:
	std::string name;
	unsigned int id;
	bool is_forklift_certified;
	enum class Experience {
		intern = 1, junior, intermediate, senior, lead
	};
	Experience experience;

};

