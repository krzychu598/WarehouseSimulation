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
	delivery.createDelivery(500, "delivery_initial.json", "electronics", "industrial", "food_and_drinks");
	int loop_num = 0;
	while (true) {
		if (loop_num % 2 == 0) {
			delivery.setTrend();

		}
		delivery.createDelivery(10, "delivery1.json", "electronics");
		delivery.createDelivery(10, "delivery2.json", "industrial", "food_and_drinks");
		delivery.createDelivery(10, "delivery3.json", "food_and_drinks", "electronics", "industrial");
		delivery.createRequest(5, "request1.json", "electronics");
		delivery.createRequest(10, "request2.json", "industrial");
		delivery.createRequest(4, "request3.json", "food_and_drinks");
		delivery.createRequest(8, "request4.json", "electronics");
		delivery.createRequest(5, "request5.json", "food_and_drinks");
		delivery.showSupplyDemand();
		std::this_thread::sleep_for(std::chrono::seconds(15));
		loop_num++;

	}
	

	return 0;
}