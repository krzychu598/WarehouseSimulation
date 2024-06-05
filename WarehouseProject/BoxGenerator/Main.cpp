#include <iostream>
#include "Delivery.h"
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <time.h> 

int main() {
	//initialize seed
	srand(time(NULL));
	std::vector<std::string> vec = { "electronics", "food_and_drinks", "industrial" };
	Delivery delivery(vec);
	delivery.createDelivery(200, "delivery_initial.json", "electronics", "industrial", "food_and_drinks");
	delivery.createDelivery(10, "delivery1.json", "electronics");
	delivery.createDelivery(10, "delivery2.json", "industrial", "food_and_drinks");
	delivery.createDelivery(10, "delivery3.json", "food_and_drinks", "electronics", "industrial");
	delivery.createRequest(2, "request1.json", "electronics" );
	delivery.createRequest(4, "request2.json", "industrial" );
	delivery.createRequest(3, "request3.json", "food_and_drinks");
	delivery.createRequest(3, "request4.json", "electronics");
	delivery.createRequest(3, "request5.json", "food_and_drinks");

	int n;
	while (true) {
		n = 5;
		delivery.setTrend();
		delivery.createDelivery(10, "delivery1.json", "electronics");
		delivery.createDelivery(10, "delivery2.json", "industrial", "food_and_drinks");
		delivery.createDelivery(10,  "delivery3.json", "food_and_drinks", "electronics", "industrial");
		while (n != 0) {

			delivery.createRequest(2, "request1.json", "electronics");
			delivery.createRequest(4, "request2.json", "industrial");
			delivery.createRequest(3, "request3.json", "food_and_drinks");

			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

	}
	

	return 0;
}