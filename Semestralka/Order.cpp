#include "Order.h"

#include <random>

using namespace std;

Order::Order() {
	customerName_ = "";
	customerAddress_ = 0;
	productType_ = FinalProductType::Fries;
	quantity_ = 0;
	dispatched_ = false;
	deniedOrder_ = false;
	canceled_ = false;
	produced_ = false;
	delivered_ = false;
	ID_ = 0;
	orderDate_ = new Date(0, 0, 0);
	dispatchDate_ = new Date(0, 0, 0);
	deliveredDate_ = new Date(0, 0, 0);
	firmProfit_ = 0;
}

Order::~Order() {
	delete deliveredDate_;
	delete dispatchDate_;
	delete orderDate_;
	deliveredDate_ = nullptr;
	dispatchDate_ = nullptr;
	orderDate_ = nullptr;
}

double Order::getFirmProfit()
{
	return firmProfit_;
}

Order::Order(FinalProductType productType, int quantity, string customerName, int customerAddress) {
	customerName_ = customerName;
	customerAddress_ = customerAddress;
	productType_ = productType;
	quantity_ = quantity;
	//    price_ = price;
	dispatched_ = false;
	ID_ = 0;
	orderDate_ = new Date(0, 0, 0);
	dispatchDate_ = new Date(0, 0, 0);
	deliveredDate_ = new Date(0, 0, 0);
	deniedOrder_ = false;
	canceled_ = false;
	produced_ = false;
	loaded_ = false;
	delivered_ = false;

	//zisk je len nahodne vygenerovana hodnota ktora ostane ulozena ako privat atribut - v tomto pripade simulujem to, ze k tej informacii ma pristup len firma
	mt19937 rand;
	rand.seed(std::random_device{}());
	if (productType_ == FinalProductType::Fries) {
		uniform_real_distribution<double> friesRange(0.7, 4.30);
		firmProfit_ = friesRange(rand);
		firmProfit_ = firmProfit_ * quantity;
	}
	else {
		uniform_real_distribution<double> chipsRange(0.36, 5.58);
		firmProfit_ = chipsRange(rand);
		firmProfit_ = firmProfit_ * quantity;
	}
}
