#pragma once
class Employee
{
public:
	Employee();
	Employee(unsigned int p_id, bool p_is_forklift_certified);
	unsigned int getId();
	bool is_certified();
	void setId(unsigned int new_id);
	void setCertified(bool new_c);

private:
	unsigned int id;
	bool is_forklift_certified;

};

