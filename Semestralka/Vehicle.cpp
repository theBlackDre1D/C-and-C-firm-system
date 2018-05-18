

#include <iostream>
#include "Vehicle.h"
#include "structures\list\array_list.h"

using namespace structures;

//Vehicle::Vehicle(const string SPZ, FinalProductType productType) {
//	SPZ_ = SPZ;
//	firstDay_ = new Date(1, 2, 2000);
//	todayCarryCapacity_ = 0;
//	regions_ = new LinkedList<int>();
//	switch (productType) {
//	case FinalProductType::Fries:
//		vehicleType_ = VehicleType::FriesVehicle;
//		carryCapacity_ = 5000;
//		break;
//	case FinalProductType::Chips:
//		vehicleType_ = VehicleType::ChipsVehicle;
//		carryCapacity_ = 2000;
//		break;
//	default:
//		break;
//	}
//	totalShipmentPrice_ = 0;
//	ordersIDs_ = new LinkedList<int>();
//}

Vehicle::Vehicle(string SPZ, int productType)
{
	SPZ_ = SPZ;
	firstDay_ = new Date(1, 2, 2000);
	todayCarryCapacity_ = 0;
	regions_ = new LinkedList<int>();
	switch (productType) {
	case 1:
		vehicleType_ = VehicleType::FriesVehicle;
		carryCapacity_ = 5000;
		break;
	case 2:
		vehicleType_ = VehicleType::ChipsVehicle;
		carryCapacity_ = 2000;
		break;
	default:
		break;
	}
	totalShipmentPrice_ = 0;
	ordersIDs_ = new LinkedList<int>();
}

Vehicle::~Vehicle() {
	delete firstDay_;
	delete regions_;
	delete ordersIDs_;
	ordersIDs_ = nullptr;
	regions_ = nullptr;
	firstDay_ = nullptr;
	
}

void Vehicle::addRegion(int regionNumber) {
	if (regions_->getIndexOf(regionNumber) != -1) {
		regions_->add(regionNumber);
		shippingPrice_ += (vehicleType_ == VehicleType::FriesVehicle) ? 100 : 70;
	}
	else {
		cout << "This region is already included." << endl;
	}
}
