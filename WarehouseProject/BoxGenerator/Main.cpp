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
	delivery.setTrend();
	while (true) {
		delivery.updateDemand();
		delivery.createDelivery(10, "electronics", "electronics", "delivery1.json");

		/*delivery.createDelivery(10, "industrial", "industrial", "delivery2.json");
		delivery.createDelivery(10, "food_and_drinks", "industrial", "delivery3.json");
		delivery.createRequest(10, "food_and_drinks", "request1.json");
		delivery.createRequest(10, "electronics", "request2.json");
		delivery.createRequest(10, "industrial", "request3.json");
		*/
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	return 0;
}