#pragma once
#include <string>

#include "FinalProductType.h"
#include "VehicleType.h"
#include "Date.h"
#include "structures\list\linked_list.h"


using namespace std;
using namespace structures;

class Array;

class Vehicle {
public:
	//Vehicle();
	//Vehicle(string SPZ, FinalProductType productType);
	Vehicle(string SPZ, int productType);
	~Vehicle();

	void addRegion(int regionNumber);

	string SPZ_;
	VehicleType vehicleType_;
	int carryCapacity_; // in kg
	//int regionsCount_;
	int shippingPrice_;
	int totalShipmentPrice_;
	int todayCarryCapacity_;
	Date *firstDay_;
	LinkedList<int> *regions_;
	LinkedList<int> *ordersIDs_;

	//    void setRegionsCount(int count);

};