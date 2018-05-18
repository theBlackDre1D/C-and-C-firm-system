#pragma once

#include "structures\list\linked_list.h"

#include "Biofarmar.h"
#include "Vehicle.h"
#include "Order.h"
#include "Customer.h"
#include "SemiProductOrder.h"

using namespace structures;

class Firm {
public:
	Firm();
	~Firm();

	LinkedList<Biofarmar *> *biofarmars_;
	LinkedList<Vehicle *> *vehicles_;
	LinkedList<Order *> *orders_;
	LinkedList<Customer *> *customers_;
	LinkedList<SemiProductOrder *> *ordersFromBiofarmars_;
	Date *todayDate_;

	void addBiofarmar(Biofarmar &newBiofarmar);
	//void addBiofarmar(string name, int productType);
	void addVehicles(string SPZ, FinalProductType productType);
	void addCustomer(Customer &customer);
	void showBiofarmarsWithProduct(int index);
	void showVehicles();
	void createNewOrderAs(Customer &customer, int quantity, Date &dispatchDate, FinalProductType productType);
	void checkStock();
	void showOrdersForTomorrow();
	void goToTheNextDay();
	void fillVehicles();
	void deliverGoods();
	void showCustomersInRegionWithTimePeriod(int region, Date &since, Date &to);
	void showSuccessfulOrderInTimePeriod(Date &since, Date &to);
	void showUnsuccessfulOrderInTimePeriod(Date &since, Date &to);
	void checkNewOrder(Order &newOrder);
	//void checkNewOrder(Order &newOrder, Date &orderDate ,Date &dispatchDate);
	void addProductToBiofarmar(int productNumber, Biofarmar * biofarmar);
	void findBestBiofarmarWithProduct(int typeNumber);
	void saveStateOfFirmToFile();
	void profitInTimePeriod(Date &since, Date &to);

	int getPotatoesStock();
	int getOilStock();
	int getFlavorsStock();


private:
	double totalCarryCapacityFriesCars_;
	double totalCarryCapacityChipsCars_;

	double todayFriesCarsCapacity_;
	double todayChipsCarsCapacity_;

	// zasoby
	double potatoesStock_;
	double oilStock_;
	double flavorsStock_;


	void refillPotatoes(int desiredPotatoes);
	void refillOil(int desiredOil);
	void refillFlavors(int desiredFlavors);
	void produce();
	//bool compareFunction(Order a, Order b);
	//int findRightIndex(Customer &customer1, Customer &customer2);

};
