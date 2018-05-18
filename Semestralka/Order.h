#pragma once


#include "FinalProductType.h"
#include "Customer.h"
#include "Date.h"

class Order {
public:
	Order();
	Order(FinalProductType productType, int quantity, string customerName, int customerAddress);
	~Order();

	Date *orderDate_;
	Date *dispatchDate_;
	Date *deliveredDate_;
	string customerName_;
	int customerAddress_;
	FinalProductType productType_;
	int quantity_;
	int price_;
	bool deniedOrder_; // zamietnuta
	bool canceled_; // zrusena
	bool dispatched_;
	bool delivered_;
	bool produced_;
	bool loaded_;
	int ID_;

	double getFirmProfit();
private:
	double firmProfit_;
};
