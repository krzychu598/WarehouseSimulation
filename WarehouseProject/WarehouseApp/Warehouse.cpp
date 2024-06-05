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
		std::vector<Employee> new_employees;
		for (const auto& employee : team["employees"]) {
			new_employees.push_back(Employee(employee));
		}
		work_types[team["work_type"]] = new_employees;
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
};
bool Warehouse::reviewDelivery(const std::string& file_name) {
	PRINT_MSG("\nReviewing New Delivery ", file_name, "");
	nlohmann::json delivery_json = getJsonData(FOLDER + file_name);
	if (delivery_json["size"]["size"].get<int>() > size - occupied_space_size) {
		std::cout << "Delivery doesn't fit in the Warehouse\n";
		return false;;
	}
	for (const auto& item : delivery_json["size"].items()) {

		for (const auto& area : areas) {

			if ((area)->getType() == item.key()) {
				if ((area)->getEmptySpace() < item.value()) {
					std::cout << "Delivery doesn't fit in the Warehouse\n";
					return false;
				}
			};
		};
	};
	std::cout << "Delivery accepted\n";
	return true;
};
bool Warehouse::reviewRequest(const std::string& file_name) {
	PRINT_MSG("\nReviewing New Request ", file_name, "");
	nlohmann::json delivery_json = getJsonData(FOLDER + file_name);
	for (auto& product : delivery_json.at("products")) {
		if (!this->find(product["product_name"], product["quantity"], delivery_json["type"])) {
			std::cout << "delivery cannot be sent. Not enough " << product["product_name"] << '\n';
			return false;
		};
	};
	std::cout << "request can be fulfilled\n";
	return true;
};

void Warehouse::acceptDelivery(const std::string& file_name) {
	if (!reviewDelivery(file_name)) {
		return;
	}

	//TODO check employee availability
	PRINT_MSG("\Processing delivery ", file_name, "");

	nlohmann::json delivery_json = getJsonData(FOLDER + file_name);
	unsigned int delivery_size = delivery_json["size"]["size"].get<int>();
	occupied_space_size += delivery_size;
	for (const auto& box : delivery_json["boxes"]) {
		this->put(box);
	};
	PRINT_MSG("Successfully accepted ", file_name, " delivery");

};

void Warehouse::sendDelivery(const std::string& file_name) {
	if (!reviewRequest(file_name)) {
		return;
	}

	PRINT_MSG("\nProcessing request ", file_name, "");

	nlohmann::json delivery_data = getJsonData(FOLDER + file_name);
	Box box;
	int n;
	for (const auto& product : delivery_data.at("products")) {
		n = product.at("quantity");
		while (n != 0) {
			box.put(std::move(this->get((product.at("product_name").get<std::string>()), delivery_data["type"])));
			PRINT_MSG("", product.at("product_name"), " put in a delivery box");
			n--;
		}

	}
	PRINT_MSG("Successfully processed ", file_name, " request");
};

void Warehouse::startWorking(const std::vector<std::string>& deliveries, const std::vector<std::string>& requests) {
	//current date
	time_t now = time(0);
	struct tm time_struct;
	errno_t err = localtime_s(&time_struct, &now);
	if (err != NULL) throw std::runtime_error("time error");

	int n;

	//main work loop
	while (true) {
		n = 5;
		//print out date
		int now_day = time_struct.tm_mday;
		int now_month = 1 + time_struct.tm_mon;
		int now_year = 1900 + time_struct.tm_year;
		std::cout << '\n' << now_day << '.' << now_month << '.' << now_year <<'\n';

		acceptDelivery("delivery_test.json");
		sendDelivery("request_test.json");
		sendDelivery("request_test.json");

		/*
		//process available deliveries and requests
		for (auto& delivery : deliveries) {
			acceptDelivery(delivery);
		}
		for (auto& request : requests) {
			sendDelivery(request);
		}
		*/


		//update date
		time_struct.tm_mday++;
		now = mktime(&time_struct);
		errno_t err = localtime_s(&time_struct, &now);
		if (err != 0) throw std::runtime_error("time error");
		std::this_thread::sleep_for(std::chrono::seconds(5));

	}
	
}

void Warehouse::assignToJob(const std::string& work_type, unsigned int work_load) {
	
};
