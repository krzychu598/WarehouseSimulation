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
	Delivery delivery;
	delivery.createDelivery(20, "initial_delivery.json", "electronics", "industrial", "food_and_drinks");
	while (true) {
		delivery.setTrend();
		delivery.updateDemand();
		delivery.createDelivery(10, "delivery1.json", "electronics");
		delivery.createDelivery(10, "delivery2.json", "industrial", "food_and_drinks");
		delivery.createDelivery(10,  "delivery3.json", "food_and_drinks", "electronics", "industrial");

		delivery.createRequest(2, "electronics", "request1.json");
		delivery.createRequest(3, "electronics", "request1.json");
		delivery.createRequest(4, "electronics", "request1.json");

		delivery.createRequest(2, "industrial", "request2.json");
		delivery.createRequest(3, "industrial", "request2.json");
		delivery.createRequest(4, "industrial", "request2.json");

		delivery.createRequest(2, "food_and_drinks", "request3.json");
		delivery.createRequest(3, "food_and_drinks", "request3.json");
		delivery.createRequest(4, "food_and_drinks", "request3.json");

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}

	return 0;
}