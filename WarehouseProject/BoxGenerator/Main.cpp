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
	while (true) {
		delivery.setTrend();
		delivery.updateDemand();
		delivery.createDelivery(10, "electronics", "industrial", "delivery1.json");
		delivery.createDelivery(10, "industrial", "food_and_drinks", "delivery2.json");
		delivery.createDelivery(10, "food_and_drinks", "electronics", "delivery3.json");
		delivery.createRequest(3, "electronics", "request1.json");
		delivery.createRequest(4, "industrial", "request2.json");
		delivery.createRequest(5, "food_and_drinks", "request3.json");
		break;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	return 0;
}