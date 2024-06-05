#include "Warehouse.h"

Warehouse::Warehouse(const std::string& file_path) : StorageSpace() {
	nlohmann::json json_data = getJsonData(file_path);

	name = json_data.at("name");
	size = json_data.at("size").get<unsigned int>();

	//initialize Areas
	for (const auto& area_json : json_data["areas"]) {
		areas.push_back(std::make_unique<Area>(
			area_json
		));
	}

	//Initialize Employees
	for (const auto& team : json_data["teams"]) {
		Team new_team;
		for (const auto& employee : team["employees"]) {
			Employee new_employee(employee);
			new_team.addEmployee(new_employee);
		}
		work_types[team["work_type"]] = new_team;
	}
	PRINT_MSG("Warehouse ", name, " created");
}

Warehouse::~Warehouse() {
	PRINT_MSG("\nWarehouse ", name, " destroyed");
}

void Warehouse::put(const nlohmann::json& box) {
	for (auto& area : areas) {
		if ((area)->getType() == box["type"]) {
			(area)->put(box);
			occupied_space_size++;
			return;
		}
	}
	PRINT_MSG("Couldn't put: ", box["product_name"], "");
	PRINT_MSG("No appropiate area: ", box["type"], "");
}

bool Warehouse::find(std::string name, int amount, std::string type) const {
	for (auto& area : areas) {

		if (type == "undefined") {
			if (!area->find(name,amount)) {
				continue;
			};
			//PRINT_MSG("object ", name, " found");
			return true;

		}

		if (area->getType() == type) {
			bool result = area->find(name, amount);
			//PRINT_MSG_N("object ", name, result, " found");
			return result;
		}
	}
	PRINT_MSG("object ", name, " not found");
	return false;
}

std::unique_ptr<Product> Warehouse::get(std::string&& name, std::string type) {
	for (auto& area : areas) {

		if (area->getType() == type) {
			return std::move(area->get(name));
		}
	}
	PRINT_MSG("Couldn't get ", name, "");
	return nullptr;
};
bool Warehouse::reviewDelivery(const std::string& file_name) {
	PRINT_MSG("\nReviewing New Delivery ", file_name, "");
	nlohmann::json delivery_json = getJsonData(FOLDER + file_name);

	//is data correct?
	try {
		delivery_json.at("boxes");
	}
	catch (...) {
		return false;
	}

	//does delivery fit in the warehouse?
	if (delivery_json["size"]["size"].get<unsigned int>() > getEmptySpace()) {
		PRINT("Delivery doesn't fit in the Warehouse");
		return false;
	}
	for (const auto& item : delivery_json["size"].items()) {

		for (const auto& area : areas) {

			if ((area)->getType() == item.key()) {
				if ((area)->getEmptySpace() < item.value()) {
					PRINT("Delivery doesn't fit in the Warehouse");
					return false;
				}
			};
		};
	};

	//are there enough employees
	if (work_types["storage_managment"].current_work_capacity < delivery_json["size"]["size"].get<unsigned int>()) {
		PRINT("Not enough employees to take care of delivery");
		return false;
	}
	PRINT("Delivery accepted");
	return true;
};
bool Warehouse::reviewRequest(const std::string& file_name) {
	PRINT_MSG("\nReviewing New Request ", file_name, "");
	nlohmann::json delivery_json = getJsonData(FOLDER + file_name);

	//is data correct?
	try {
		delivery_json.at("products");
	}
	catch (...) {
		return false;
	}

	//are there enough items in the warehouse?
	unsigned int work_load = 0;
	unsigned int extra_work_load = 0;

	for (auto& product : delivery_json.at("products")) {
		work_load += product.at("quantity");
		if (!this->find(product["product_name"], product["quantity"], delivery_json["type"])) {
			PRINT_MSG("delivery cannot be sent. Not enough ", product["product_name"], "");
			return false;
		}
		else {		//update work force needed if product is placed on shelf with low priority
			extra_work_load += this->getExtraWorkLoad(product["product_name"], delivery_json["type"]);	// if A->+0, if B->+1, if C->+2
		}
	};
	work_load += extra_work_load;
	//is there enough work force to perform the job?
	if (work_types["packaging"].current_work_capacity < work_load) {
		PRINT_MSG("Not enough employees to take care of request. Extra work load: ", extra_work_load, "");
		return false;
	}
	PRINT_MSG("request accepted. Extra work load: ", extra_work_load, "");
	return true;
};
unsigned int Warehouse::getExtraWorkLoad(const std::string& name, const std::string& type) const {
	unsigned int additional_work_load = 0;
	for (const auto& area : areas) {
		if (area->getType() == type) {
			additional_work_load += area->getExtraWorkLoad(name);
			break;
		}
	}
	return additional_work_load;
}

void Warehouse::acceptDelivery(const std::string& file_name, bool initial) {
	if ((!initial) && (!reviewDelivery(file_name))) {
		return;
	}

	PRINT_MSG("\Processing delivery ", file_name, "");

	nlohmann::json delivery_json = getJsonData(FOLDER + file_name);
	unsigned int delivery_size = delivery_json["size"]["size"].get<int>();
	occupied_space_size += delivery_size;
	for (const auto& box : delivery_json["boxes"]) {
		this->put(box);
	};
	PRINT_MSG("Successfully processed ", file_name, " delivery");
	if(!initial) work_types["storage_managment"].current_work_capacity -= delivery_json["size"]["size"];
};

void Warehouse::sendDelivery(const std::string& file_name) {
	if (!reviewRequest(file_name)) {
		return;
	}

	PRINT_MSG("Processing request ", file_name, "");

	nlohmann::json delivery_data = getJsonData(FOLDER + file_name);
	Box box;
	int n;
	unsigned int all_items = 0;
	for (const auto& product : delivery_data.at("products")) {
		n = product.at("quantity");
		all_items += n;
		while (n != 0) {
			box.put(std::move(this->get((product.at("product_name").get<std::string>()), delivery_data["type"])));
			PRINT_MSG("", product.at("product_name"), " put in a delivery box");
			n--;
		}

	}
	PRINT_MSG("Successfully processed ", file_name, " request");
	work_types["packaging"].current_work_capacity -= all_items;
};

void Warehouse::startWorking(const std::vector<std::string>& deliveries, const std::vector<std::string>& requests) {
	//current date
	time_t now = time(0);
	struct tm time_struct;
	errno_t err = localtime_s(&time_struct, &now);
	if (err != NULL) throw std::runtime_error("time error");

	employeeRest();


	//main work loop
	while (true) {
		//print out date
		int now_day = time_struct.tm_mday;
		int now_month = 1 + time_struct.tm_mon;
		int now_year = 1900 + time_struct.tm_year;
		PRINT_MSG_L('\n', now_day, '.');
		PRINT_MSG_L("", now_month, '.');
		PRINT_MSG("", now_year, "");
		std::this_thread::sleep_for(std::chrono::seconds(2));

		/*	Test cases
		acceptDelivery("delivery_test.json");
		sendDelivery("request_test.json");
		sendDelivery("request_test.json");
		sendDelivery("request_test.json");
		*/

		
		//process available deliveries and requests
		for (auto& delivery : deliveries) {
			acceptDelivery(delivery);
			std::this_thread::sleep_for(std::chrono::seconds(5));

		}
		for (auto& request : requests) {
			sendDelivery(request);
			std::this_thread::sleep_for(std::chrono::seconds(5));

		}
		



		
		//update date
		time_struct.tm_mday++;
		now = mktime(&time_struct);
		errno_t err = localtime_s(&time_struct, &now);
		if (err != 0) throw std::runtime_error("time error");

		//end of day
		updatePlacement();
		PRINT("Placement of boxes updated based on priority");
		PRINT("The day has ended");

		employeeRest();
		std::this_thread::sleep_for(std::chrono::seconds(2));


	}
	
}

void Warehouse::updatePlacement() {
	for (auto& area : areas) {
		area->updatePlacement();
	}
}

void Warehouse::employeeRest() {
	for (auto& type : work_types) {
		type.second.rest();
	}
}