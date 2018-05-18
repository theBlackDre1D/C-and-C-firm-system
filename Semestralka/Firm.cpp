
#include "Firm.h"
#include "structures\list\array_list.h"
#include "BiofarmProductType.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>


using namespace std;
using namespace structures;

Firm::Firm() {
	biofarmars_ = new LinkedList<Biofarmar *>();
	vehicles_ = new LinkedList<Vehicle *>();
	orders_ = new LinkedList<Order *>();
	customers_ = new LinkedList<Customer *>();
	todayDate_ = new Date(1, 1, 2000);
	todayChipsCarsCapacity_ = 0;
	todayFriesCarsCapacity_ = 0;
	totalCarryCapacityChipsCars_ = 0;
	totalCarryCapacityFriesCars_ = 0;
	ordersFromBiofarmars_ = new LinkedList<SemiProductOrder *>();
	potatoesStock_ = 0;
	oilStock_ = 0;
	flavorsStock_ = 0;
}

Firm::~Firm() {
	for (Order *order : *orders_)
	{
		delete order;
	}

	for (int i = 0; i < vehicles_->size(); i++)
	{
		delete (*vehicles_)[i];
	}

	for (int i = 0; i < biofarmars_->size(); i++)
	{
		delete (*biofarmars_)[i];
	}

	for (int i = 0; i < ordersFromBiofarmars_->size(); i++)
	{
		delete (*ordersFromBiofarmars_)[i];
	}

	for (int i = 0; i < customers_->size(); i++)
	{
		delete (*customers_)[i];
	}

	orders_->clear();
	vehicles_->clear();
	biofarmars_->clear();
	ordersFromBiofarmars_->clear();
	customers_->clear();
	delete orders_;
	delete vehicles_;
	delete biofarmars_;
	delete todayDate_;
	delete ordersFromBiofarmars_;
	delete customers_;
	orders_ = nullptr;
	vehicles_ = nullptr;
	biofarmars_ = nullptr;
	todayDate_ = nullptr;
	customers_ = nullptr;
	ordersFromBiofarmars_ = nullptr;
}

void Firm::addBiofarmar(Biofarmar &newBiofarmar) {
	if (biofarmars_->size() == 0) {
		biofarmars_->add(&newBiofarmar);
	}
	else {
		if (biofarmars_->getIndexOf(&newBiofarmar) == -1) {
			biofarmars_->add(&newBiofarmar);
		}
	}
	
}

void Firm::addCustomer(Customer &customer)
{
	if (customers_->size() == 0) {
		customers_->add(&customer);
	}
	else
	{
		int index = customers_->getIndexOf(&customer);
		if (customers_->getIndexOf(&customer) == -1) { // ak funkcia getIndexOf vrati -1 znamena to, ze tam nie je pozadovany prvok a mozme ho pridat
			customers_->add(&customer);
		}
	}
	
}

void Firm::showBiofarmarsWithProduct(const int index) {
	//    sort(biofarmars_->begin(), biofarmars_->end());
	if (index > 3) {
		cout << "You must enter number in range <1,3>." << endl;
	}
	else
	{
		// Bublesort
		for (int j = 0; j < biofarmars_->size() - 1; j++)
		{
			for (int i = 0; i < biofarmars_->size() - 1; i++)
			{
				if (i + 1 <= biofarmars_->size() - 1 && (*biofarmars_)[i]->businessName_ >(*biofarmars_)[i + 1]->businessName_)
				{
					Biofarmar *tmpBiofarmar = (*biofarmars_)[i];
					(*biofarmars_)[i] = (*biofarmars_)[i + 1];
					(*biofarmars_)[i + 1] = tmpBiofarmar;
				}
			}
		}	

		cout << "Name   " << "Products          " << "Average price		" << endl;
		switch (index) 
		{
			case 1: 
			{
				for (Biofarmar *biofarmar : *biofarmars_) 
				{
					if (biofarmar->hasPotatoes)
					{
						//LinkedList<int> *prices = new LinkedList<int>();
						int prices = 0;
						int count = 0;
						for (SemiProductOrder *order : *ordersFromBiofarmars_)
						{
							if (order->biofarmarName_ == biofarmar->businessName_ && order->type_ == BiofarmProductType::Potato)
							{
								prices = prices + order->price_;
								count++;
							}
						}
						double averagePrice = prices / count;
						cout << biofarmar->businessName_ << " products: " << (biofarmar->hasPotatoes ? "Potatoes " : " ")
							<< (biofarmar->hasOil ? "Oil " : " ") << (biofarmar->hasFlavors ? "Flavors" : " ") << averagePrice << endl;
					}
				}
				break;
			}
			case 2: 
			{
				for (Biofarmar *it : *biofarmars_) 
				{
					if (it->hasOil) 
					{
						int prices = 0;
						int count = 0;
						for (SemiProductOrder *order : *ordersFromBiofarmars_)
						{
							if (order->biofarmarName_ == it->businessName_ && order->type_ == BiofarmProductType::Oil)
							{
								prices = prices + order->price_;
								count++;
							}
						}
						double averagePrice = prices / count;
						cout << it->businessName_ << " products: " << (it->hasPotatoes ? "Potatoes " : " ")
							<< (it->hasOil ? "Oil " : " ") << (it->hasFlavors ? "Flavors" : " ") << averagePrice << endl;
					}
				}
				break;
			}
			case 3: 
			{
				for (Biofarmar *it : *biofarmars_) 
				{
					if (it->hasFlavors) 
					{
						int prices = 0;
						int count = 0;
						for (SemiProductOrder *order : *ordersFromBiofarmars_)
						{
							if (order->biofarmarName_ == it->businessName_ && order->type_ == BiofarmProductType::Flavors)
							{
								prices = prices + order->price_;
								count++;
							}
						}
						double averagePrice = prices / count;
						cout << it->businessName_ << " products: " << (it->hasPotatoes ? "Potatoes " : " ")
							<< (it->hasOil ? "Oil " : " ") << (it->hasFlavors ? "Flavors" : " ") << averagePrice << endl;
					}
				}
				break;
			}
		}
	}
}


void Firm::showVehicles() {
	cout << "SPZ    " << "Product   " << "First day     " << "Total shipment price" << endl;
	// buble sort
	for (int j = 0; j < vehicles_->size() - 1; j++)
	{
		for (int i = 0; i < vehicles_->size() - 1; i++)
		{
			if (i + 1 <= vehicles_->size() - 1 && (*vehicles_)[i + 1]->firstDay_->isBigger(*(*vehicles_)[i]->firstDay_) == false)
			{
				Vehicle *tmpVehicle = (*vehicles_)[i];
				(*vehicles_)[i] = (*vehicles_)[i + 1];
				(*vehicles_)[i] = tmpVehicle;
			}
		}
	}

	for (Vehicle *it : *vehicles_) { // ma byt podla zaradenia do evidencie zoradene
		cout << it->SPZ_ << " " << (it->vehicleType_ == VehicleType::FriesVehicle ? "FriesVehicle " : "ChipsVehicle ")
			<< it->firstDay_->toString() << " " << it->totalShipmentPrice_ << endl;
	}
}

void Firm::addVehicles(const string SPZ, FinalProductType productType) {
	bool isInVehicle = true;
	if (vehicles_->size() == 0) {
		isInVehicle = false;
	}
	else {
		for (Vehicle *it : *vehicles_) {
			if (it->SPZ_ == SPZ) {
				//            isInVehicle = true;
				cout << "Vehicle with this SPZ already exists. Invoke function again and enter different SPZ." << endl;
			}
			else {
				isInVehicle = false;
			}
		}
	}
	
	if (!isInVehicle) {
		Vehicle *newVehicle = new Vehicle(SPZ, productType);
		delete newVehicle->firstDay_;
		newVehicle->firstDay_ = new Date(*todayDate_);

		vehicles_->add(newVehicle);
		switch (newVehicle->vehicleType_) {
		case VehicleType::FriesVehicle:
			totalCarryCapacityFriesCars_ = totalCarryCapacityFriesCars_ + newVehicle->carryCapacity_;
			break;
		case VehicleType::ChipsVehicle:
			totalCarryCapacityChipsCars_ = totalCarryCapacityChipsCars_ + newVehicle->carryCapacity_;
			break;
		}
	}
}

void Firm::checkNewOrder(Order &newOrder) {
	
	if (todayDate_->differenceBetweenDates(*newOrder.dispatchDate_) > 7) {
		int latestOrderID = (orders_->size() == 0) ? 0 :(*orders_)[orders_->size() - 1]->ID_; // tu pridavam ID objednavky
		
		switch (newOrder.productType_) {
		case FinalProductType::Fries: // Fries vehicles
			newOrder.price_ = 6;
			newOrder.ID_ = latestOrderID + 1;

			orders_->add(&newOrder);
			break;

		case FinalProductType::Chips: // Chips vehicles
			newOrder.price_ = 8;
			newOrder.ID_ = latestOrderID + 1;
			orders_->add(&newOrder);
			
			break;
		}
	}
	else {
		cout << "Order was not accepted. You must make order at least 7 day before your dispatch day." << endl;
	}
}

void Firm::addProductToBiofarmar(int productNumber, Biofarmar * biofarmar)
{
	biofarmar->addProduct(productNumber);
}

void Firm::findBestBiofarmarWithProduct(int typeNumber)
{
	BiofarmProductType type;
	if (typeNumber == 1)
	{
		type = BiofarmProductType::Potato;
	}
	else if (typeNumber == 2)
	{
		type = BiofarmProductType::Oil;
	}
	else
	{
		type = BiofarmProductType::Flavors;
	}


	for (SemiProductOrder *order : *ordersFromBiofarmars_) {
		for (Biofarmar *biofarmar : *biofarmars_) {
			if (order->biofarmarName_ == biofarmar->businessName_) {
				biofarmar->kilosCount_ = biofarmar->kilosCount_ + order->quantity_;
				biofarmar->pricesCount_ = biofarmar->pricesCount_ + order->price_;
				biofarmar->orderCount_++;
				biofarmar->count_++;
			}
		}
	}

	Biofarmar *tmpBiofarmar = new Biofarmar("", 1);
	for (Biofarmar * biofarmar : *biofarmars_) {
		if (tmpBiofarmar->count_ < biofarmar->count_) {
			tmpBiofarmar = new Biofarmar(*biofarmar);
		}
	}
	double averagePrice = tmpBiofarmar->pricesCount_ / tmpBiofarmar->orderCount_;


	cout << tmpBiofarmar->businessName_ << " | " << tmpBiofarmar->kilosCount_ << " | " << tmpBiofarmar->pricesCount_ << " | " << averagePrice << endl;

	for (Biofarmar *biofarmar : *biofarmars_) {
		biofarmar->count_ = 0;
		biofarmar->pricesCount_ = 0;
		biofarmar->kilosCount_ = 0;
		biofarmar->orderCount_ = 0;
	}
	
}

void Firm::saveStateOfFirmToFile()
{
	ofstream outputFile("evidence.txt");
	outputFile << "Firm evidence from 1.1.2000 to " << todayDate_->toString() << endl;
	outputFile << "====================================================================" << endl;
	outputFile << "Stock:" << endl
		<< "Potatoes: " << potatoesStock_ << endl
		<< "Oil: " << oilStock_ << endl
		<< "Flavors: " << flavorsStock_ << endl;
	outputFile << "====================================================================" << endl;
	outputFile << "Vehicles: " << endl;
	outputFile << "SPZ	" << "First day	| " << "total shipment price | " << "Type | " << endl;
	for (Vehicle *vehicle : *vehicles_)
	{
		outputFile << vehicle->SPZ_ << " | " << vehicle->firstDay_->toString() << " | " << vehicle->totalShipmentPrice_ << " | "
			<< (vehicle->vehicleType_ == VehicleType::FriesVehicle ? "Fries vehicle" : "Chips vehicle") << endl;
	}

	outputFile << "====================================================================" << endl;
	outputFile << "Biofarmars: " << endl;
	outputFile << "Name	" << "products" << endl;
	for (Biofarmar *biofarmar : *biofarmars_)
	{
		outputFile << biofarmar->businessName_ << " | products: " << (biofarmar->hasPotatoes ? "Potatoes | " : "") << (biofarmar->hasOil ? "Oil | " : "") 
			<< (biofarmar->hasFlavors ? "Flavors | " : "") << endl;
	}

	outputFile << "====================================================================" << endl;
	outputFile << "Customers: " << endl;
	outputFile << "Name	| " << "Address	" << endl;
	for (Customer *customer : *customers_)
	{
		outputFile << customer->name_ << " " << customer->address_ << endl;
	}

	outputFile << "====================================================================" << endl;
	outputFile << "Orders: " << endl;
	outputFile << "ID | " << "Price(eur) | " << "Quantity(kg) | " << "Name | " << "Address | " << "Order date | " << "Product | " << "Delivered	| " 
		<< "Dispatched | " << "Denied | " << "Canceled | " << "Firm profit | " << endl;
	for (Order *order : *orders_)
	{
		outputFile << order->ID_ << " | " << order->price_ << " | " << order->quantity_ << " | " << order->customerName_ << " | " << order->customerAddress_ << " | "
			<< order->orderDate_->toString() << " | " << (order->productType_ == FinalProductType::Fries ? "Fries | " : "Chips | ")
			<< (order->delivered_ ? order->deliveredDate_->toString() : "Not delivered | ") << (order->dispatched_ ? order->dispatchDate_->toString() : "Not dispatched | ") 
			<< (order->deniedOrder_ ? " Denied | " : " Not denied | ") << (order->canceled_ ? "Canceled | " : "Not canceled | ") << " " <<  order->getFirmProfit() << endl;
	}

	outputFile << "====================================================================" << endl;
	outputFile << "Orders from biofarmars: " << endl;
	outputFile << "Name	| " << "Price | " << "Quantity | " << "Purchase date | " << "Semiproduct type" << endl;
	for (SemiProductOrder *order : *ordersFromBiofarmars_)
	{
		outputFile << order->biofarmarName_ << " | " << order->price_ << " | " << order->quantity_ << " | " << order->purchaseDate_->toString() << " | ";
		if (order->type_ == BiofarmProductType::Potato)
		{
			outputFile << "Potatoes" << endl;
		}
		else if (order->type_ == BiofarmProductType::Oil)
		{
			outputFile << "Oil" << endl;
		}
		else
		{
			outputFile << "Flavors" << endl;
		}
	}

	outputFile.close();

}

void Firm::profitInTimePeriod(Date & since, Date & to)
{
	int profitFries = 0;
	int profitChips = 0;
	int friesRegions = 0;
	int chipsRegions = 0;
	Date tmpDate = to;
	tmpDate.oneDayForward();
	//since.oneDayForward();
	for (Order *order : *orders_) {
		if (!since.isEqual(tmpDate)) {
			if (order->delivered_ == true && order->deliveredDate_->isEqual(since)) {
				if (order->productType_ == FinalProductType::Fries) {
					profitFries = profitFries + order->getFirmProfit();
					friesRegions++;
				}
				else {
					profitChips = profitChips + order->getFirmProfit();
					chipsRegions++;
				}
			}
			since.oneDayForward();
		}
	}

	Date tmpDate2 = to;
	tmpDate2.oneDayForward();
	int productsPrice = 0;
	for (SemiProductOrder *order : *ordersFromBiofarmars_) {
		if (!since.isEqual(tmpDate2)) {
			productsPrice = productsPrice + order->price_;
		}
		since.oneDayForward();
	}
	
	profitFries = profitFries - 100 * friesRegions;
	profitChips = profitChips - 70 * chipsRegions;
	int totalProfit = profitFries + profitChips - productsPrice;
	cout << "Total profit from this time period is: " << totalProfit << endl;

}

void Firm::refillPotatoes(int desiredPotatoes)
{
	int difference = abs(potatoesStock_ - desiredPotatoes);
	// ak nie su ziadne zaznamy v poli orderfFromBiofarmars_

	LinkedList<SemiProductOrder *> *potatoOrders = new LinkedList<SemiProductOrder *>();
	for (SemiProductOrder *order : *ordersFromBiofarmars_) 
	{
		if (order->type_ == BiofarmProductType::Potato) 
		{
			potatoOrders->add(order);
		}
	}
	// buble sort
	for (int j = 0; j < potatoOrders->size() - 1; j++)
	{
		for (int i = 0; i < potatoOrders->size() - 1; i++)
		{
			if (i + 1 <= potatoOrders->size() - 1)
			{
				if ((*potatoOrders)[i]->price_ > (*potatoOrders)[i + 1]->price_)
				{
					SemiProductOrder *tmpOrder = (*potatoOrders)[i];
					(*potatoOrders)[i] = (*potatoOrders)[i + 1];
					(*potatoOrders)[i + 1] = tmpOrder;
				}
			}
		}
	}

	for (SemiProductOrder *order : *potatoOrders)
	{
		if (difference > 0) 
		{
			for (Biofarmar *biofarmar : *biofarmars_)
			{
				if (biofarmar->hasPotatoes)
				{
					if (order->biofarmarName_ == biofarmar->businessName_ && biofarmar->potatoQuantity_ > 0)
					{
						SemiProductOrder *newOrder = new SemiProductOrder(biofarmar->businessName_, *todayDate_);
						newOrder->price_ = biofarmar->potatoPrice_;

						if (difference > biofarmar->potatoQuantity_)
						{
							newOrder->quantity_ = biofarmar->potatoQuantity_;
							difference = difference - biofarmar->potatoQuantity_;
							biofarmar->potatoQuantity_ = 0;
						}
						else
						{
							newOrder->quantity_ = difference;
							biofarmar->potatoQuantity_ = biofarmar->potatoQuantity_ - difference;
							difference = 0;
						}
						newOrder->type_ = BiofarmProductType::Potato;
						ordersFromBiofarmars_->add(newOrder);
					}
				}
			}
		}
	}
}

void Firm::refillOil(int desiredOil)
{
	double difference = abs(oilStock_ - desiredOil);

	LinkedList<SemiProductOrder *> *oilOrders = new LinkedList<SemiProductOrder *>();
	for (SemiProductOrder *order : *ordersFromBiofarmars_)
	{
		if (order->type_ == BiofarmProductType::Oil)
		{
			oilOrders->add(order);
		}
	}

	// buble sort
	for (int j = 0; j < oilOrders->size() - 1; j++)
	{
		for (int i = 0; i < oilOrders->size() - 1; i++)
		{
			if (i + 1 <= oilOrders->size() - 1)
			{
				if ((*oilOrders)[i]->price_ >(*oilOrders)[i + 1]->price_)
				{
					SemiProductOrder *tmpOrder = (*oilOrders)[i];
					(*oilOrders)[i] = (*oilOrders)[i + 1];
					(*oilOrders)[i + 1] = tmpOrder;
				}
			}
		}
	}

	for (SemiProductOrder *order : *oilOrders)
	{
		if (difference > 0)
		{
			for (Biofarmar *biofarmar : *biofarmars_)
			{
				if (biofarmar->hasOil)
				{
					if (order->biofarmarName_ == biofarmar->businessName_ && biofarmar->oilQuantity_ > 0)
					{
						SemiProductOrder *newOrder = new SemiProductOrder(biofarmar->businessName_, *todayDate_);
						newOrder->price_ = biofarmar->oilPrice_;

						if (difference > biofarmar->oilQuantity_)
						{
							newOrder->quantity_ = biofarmar->oilQuantity_;
							biofarmar->oilQuantity_ = 0;
							difference -= biofarmar->oilQuantity_;
						}
						else
						{
							newOrder->quantity_ = difference;
							biofarmar->oilQuantity_ -= difference;
							difference = 0;
						}
						newOrder->type_ = BiofarmProductType::Oil;
						ordersFromBiofarmars_->add(newOrder);
					}
				}
			}
		}
	}
}

void Firm::refillFlavors(int desiredFlavors)
{
	double difference = abs(flavorsStock_ - desiredFlavors);

	LinkedList<SemiProductOrder *> *flavorsOrders = new LinkedList<SemiProductOrder *>();
	for (SemiProductOrder *order : *ordersFromBiofarmars_)
	{
		if (order->type_ == BiofarmProductType::Flavors)
		{
			flavorsOrders->add(order);
		}
	}
	// buble sort
	for (int j = 0; j < flavorsOrders->size() - 1; j++)
	{
		for (int i = 0; i < flavorsOrders->size() - 1; i++)
		{
			if (i + 1 <= flavorsOrders->size() - 1)
			{
				if ((*flavorsOrders)[i]->price_ >(*flavorsOrders)[i + 1]->price_)
				{
					SemiProductOrder *tmpOrder = (*flavorsOrders)[i];
					(*flavorsOrders)[i] = (*flavorsOrders)[i + 1];
					(*flavorsOrders)[i + 1] = tmpOrder;
				}
			}
		}
	}

	for (SemiProductOrder *order : *flavorsOrders)
	{
		if (difference > 0)
		{
			for (Biofarmar *biofarmar : *biofarmars_)
			{
				if (biofarmar->hasFlavors)
				{
					if (order->biofarmarName_ == biofarmar->businessName_ && biofarmar->flavorsQuantity_ > 0)
					{
						SemiProductOrder *newOrder = new SemiProductOrder(biofarmar->businessName_, *todayDate_);
						newOrder->price_ = biofarmar->flavorsQuantity_;

						if (difference > biofarmar->flavorsQuantity_)
						{
							newOrder->quantity_ = biofarmar->flavorsQuantity_;
							biofarmar->flavorsQuantity_ = 0;
							difference -= biofarmar->flavorsQuantity_;
						}
						else
						{
							newOrder->quantity_ = difference;
							biofarmar->flavorsQuantity_ -= difference;
							difference = 0;
						}
						newOrder->type_ = BiofarmProductType::Flavors;
						ordersFromBiofarmars_->add(newOrder);
					}
				}
			}
		}
	}
}

void Firm::produce()
{
	LinkedList<Order *> *todayOrders = new LinkedList<Order *>();
	for (Order *order : *orders_)
	{
		if (order->deliveredDate_->isEqual(*todayDate_))
		{
			todayOrders->add(order);
		}
	}

	for (Order *order : *todayOrders)
	{
		if (order->productType_ == FinalProductType::Fries)
		{
			potatoesStock_ = potatoesStock_ - (order->quantity_ * 1.5);
			oilStock_ = oilStock_ - (order->quantity_ * 0.2);
			order->produced_ = true;
		}
		else
		{
			potatoesStock_ = potatoesStock_ - (order->quantity_ * 2);
			oilStock_ = oilStock_ - (order->quantity_ * 0.4);
			flavorsStock_ = flavorsStock_ - (order->quantity_ * 0.02);
			order->produced_ = true;
		}
	}

	fillVehicles();
}

void Firm::checkStock() {
	Date tmpDate = *todayDate_;
	tmpDate.oneDayForward();
	Date endDate = tmpDate;
	endDate.nDaysForward(6);
	double fries = 0; // tolkoto kilo hranolcekov musim vyrobit za 7 dni
	double chips = 0; // tolkoto kilo lupienkov musim vyrobit za 7 dni
	while (!tmpDate.isEqual(endDate))
	{
		for (Order *it : *orders_) 
		{
			if (tmpDate.isEqual((*it->dispatchDate_))) 
			{
				switch (it->productType_) 
				{
					case FinalProductType::Fries:
					{
						fries = fries + it->quantity_;
						break;
					}
					case FinalProductType::Chips:
					{
						chips = chips + it->quantity_;
						break;
					}
				}
			}
		}
		tmpDate.oneDayForward();
	}
	
	// HRANOLKY: 1,5kg zemiakov + 0.2l oleja = 1 kg
	// LUPIENKY: 2,0kg zemiakov + 0,4l oleja + 0.02kg ochucovadiel = 1kg
	int desiredPotatoes = fries * 1.5 + chips * 2.0;
	int desiredOil = fries * 0.2 + chips * 0.4;
	int desiredFlavours = chips * 0.02;

	// ================ TESTING =================
	//potatoesStock_ = 0;
	//oilStock_ = 0;
	//flavorsStock_ = 0;

	if (desiredPotatoes > potatoesStock_) { // Zemiaky
		refillPotatoes(desiredPotatoes);
	}
	if (desiredOil > oilStock_) { // olej
		refillOil(desiredOil);
	}

	if (desiredFlavours > flavorsStock_) { // ochucovadla
		refillFlavors(desiredFlavours);
	}
}

void Firm::createNewOrderAs(Customer &customer, int quantity, Date &dispatchDate, FinalProductType productType) {
	Order *newOrder = new Order();
	delete newOrder->orderDate_;
	newOrder->orderDate_ = new Date(*todayDate_);
	newOrder->customerName_ = customer.name_;
	newOrder->customerAddress_ = customer.address_;
	newOrder->quantity_ = quantity;
	delete newOrder->dispatchDate_;
	newOrder->dispatchDate_ = new Date(dispatchDate);
	newOrder->productType_ = productType;
	if (productType == FinalProductType::Fries) {
		newOrder->price_ = 6;
	}
	else
	{ // FinalProductType::Chips
		newOrder->price_ = 8;
	}
	checkNewOrder(*newOrder);
}

void Firm::showOrdersForTomorrow() {
	if (orders_->size() == 0) {
		cout << "Orders are empty" << endl;
	}
	else {
		cout << "Customer (region)  " << "Evidence day  " << "Type      " << "Quantity      " << "Price for unit   " << "Sales   " << "Realization" << endl;
		Date tmpDate = *todayDate_;
		tmpDate.oneDayForward();
		for (Order *it : *orders_) {
			if ((*it->dispatchDate_).isEqual(tmpDate)) {
				cout << it->customerName_ << " (" << it->customerAddress_ << ") " << (*it->orderDate_).day_ << ". " << (*it->orderDate_).month_ << ". " << (*it->orderDate_).year_ << "   "
					<< ((it->productType_ == FinalProductType::Fries) ? "Fries " : "Chips ") << it->quantity_ << " " 
					<< std::to_string(it->price_) << "eur/unit " << it->getFirmProfit() << "eur"  << (it->deniedOrder_ ? " Denied" : " Approved")
					<< (it->canceled_ ? " Canceled" : " Not canceled") << endl;
			}
		}
	}
}

void Firm::goToTheNextDay()
{
	todayDate_->oneDayForward();

	for (Biofarmar *biofarmar : *biofarmars_)
	{
		biofarmar->setPriceForToday();
	}

	for (SemiProductOrder *order : *ordersFromBiofarmars_) { // pozriem objednavky od biofarmarov ak je nejaka starsia ako 30 dni vymazem ju
		if (order->purchaseDate_->differenceBetweenDates(*todayDate_) > 30) { // hladim len do minulosti
			delete order;
		}
	}

	Date tmpTodayDate = *todayDate_;
	tmpTodayDate.oneDayBack();
	for (SemiProductOrder *order : *ordersFromBiofarmars_)
	{ // najdem tie objednavky ktore boli privezene vcera
		if (order->purchaseDate_->isEqual(tmpTodayDate))
		{
			if (order->type_ == BiofarmProductType::Potato)
			{
				potatoesStock_ += order->quantity_;
			}
			else if (order->type_ == BiofarmProductType::Oil)
			{
				oilStock_ += order->quantity_;
			}
			else
			{
				flavorsStock_ += order->quantity_;
			}
		}
	}

	// skontrolujem objednavky na zajtra ktore povolim a ktore zrusim kvoli nedostatku polotovarov
	double tmpPotatoes = potatoesStock_;
	double tmpOil = oilStock_;
	double tmpFlavors = flavorsStock_;
	for (Order *order : *orders_)
	{
		if (order->dispatchDate_->isEqual(*todayDate_))
		{
			if (order->productType_ == FinalProductType::Fries && tmpPotatoes > 0 && tmpOil > 0)
			{
				tmpPotatoes = tmpPotatoes - static_cast<double>(1.5 * order->quantity_);
				tmpOil = tmpOil - static_cast<double>(0.2 * order->quantity_);
			}
			else if (order->productType_ == FinalProductType::Fries && tmpPotatoes <= 0 && tmpOil <= 0)
			{
				order->canceled_ = true;
			}

			if (order->productType_ == FinalProductType::Chips && tmpPotatoes > 0 && tmpOil > 0 && tmpFlavors > 0)
			{
				tmpPotatoes = tmpPotatoes - static_cast<double>(2 * order->quantity_);
				tmpOil = tmpOil - static_cast<double>(0.4 * order->quantity_);
				tmpFlavors = tmpFlavors - static_cast<double>(0.02 * order->quantity_);
			}
			else if (order->productType_ == FinalProductType::Chips && tmpPotatoes <= 0 && tmpOil <= 0 && tmpFlavors <= 0)
			{
				order->canceled_ = true;
			}
		}
	}
	produce();
}

void Firm::fillVehicles()
{
	LinkedList<Order *> *friesOrders = new LinkedList<Order *>();
	LinkedList<Order *> *chipsOrders = new LinkedList<Order *>();

	for (Order *order : *orders_)
	{
		if (order->dispatchDate_->isEqual(*todayDate_)) // vyberam tie ktore maju byt dneska vyvezene
		{
			if (order->productType_ == FinalProductType::Fries && order->produced_ == true)
			{
				friesOrders->add(order);
			}
			else if (order->productType_ == FinalProductType::Chips && order->produced_ == true)
			{
				chipsOrders->add(order);
			}
		}
	}

	//buble sort fries
	if (friesOrders->size() > 0)
	{
		for (int j = 0; j < friesOrders->size() - 1; j++)
		{
			for (int i = 0; i < friesOrders->size() - 1; i++)
			{
				if (i + 1 <= friesOrders->size() - 1 && // ak iiiity prvok existuje
					(*friesOrders)[i]->customerAddress_ < (*friesOrders)[i + 1]->customerAddress_)
				{
					Order *tmpOrder = (*friesOrders)[i];
					(*friesOrders)[i] = (*friesOrders)[i + 1];
					(*friesOrders)[i + 1] = tmpOrder;
				}
			}
		}
	}

	//buble sort chips
	if (chipsOrders->size() > 0)
	{
		for (int j = 0; j < chipsOrders->size() - 1; j++)
		{
			for (int i = 0; i < chipsOrders->size() - 1; i++)
			{
				if (i + 1 <= chipsOrders->size() - 1 && // ak iiiity prvok existuje
					(*chipsOrders)[i]->customerAddress_ < (*chipsOrders)[i + 1]->customerAddress_)
				{
					Order *tmpOrder = (*chipsOrders)[i];
					(*chipsOrders)[i] = (*chipsOrders)[i + 1];
					(*chipsOrders)[i + 1] = tmpOrder;
				}
			}
		}
	}

	// naplnanie vehicles
	int friesCount = 0;
	int chipsCount = 0;
	for (Vehicle *vehicle : *vehicles_)
	{
		if (vehicle->vehicleType_ == VehicleType::FriesVehicle)
		{
			for (Order *order : *friesOrders)
			{
				if (vehicle->todayCarryCapacity_ + order->quantity_ <= vehicle->carryCapacity_ && order->loaded_ == false)
				{
					vehicle->todayCarryCapacity_ = vehicle->todayCarryCapacity_ + order->quantity_;
					vehicle->regions_->add(order->customerAddress_);
					vehicle->ordersIDs_->add(order->ID_);
					order->loaded_ = true;
				}
			}
		}
		else // VehicleType::ChipsVehicle
		{
			for (Order *order : *chipsOrders)
			{
				if (vehicle->todayCarryCapacity_ + order->quantity_ <= vehicle->carryCapacity_ && order->loaded_ == false)
				{
					vehicle->todayCarryCapacity_ = vehicle->todayCarryCapacity_ + order->quantity_;
					vehicle->regions_->add(order->customerAddress_);
					vehicle->ordersIDs_->add(order->ID_);
					order->loaded_ = true;
				}
			}
		}
	}
	// objednavky, ktore neboli nalozene urcim za zamietnute
	for (Order *order : *friesOrders)
	{
		if (order->loaded_ == false)
		{
			order->deniedOrder_ = true;
		}
	}

	for (Order *order : *chipsOrders)
	{
		if (order->loaded_ == false)
		{
			order->deniedOrder_ = true;
		}
	}
	deliverGoods();
}

void Firm::deliverGoods()
{
	for (Vehicle *vehicle : *vehicles_) {
		if (vehicle->regions_->size() > 0) {
			for (int ID : *vehicle->ordersIDs_) {
				for (Order *order : *orders_) {
					if (order->ID_ == ID) {
						order->delivered_ = true;
						delete (order->deliveredDate_);
						order->deliveredDate_ = new Date(*todayDate_);
					}
				}
			}
		}

		// Priprava vozidla na dalsi den
		vehicle->totalShipmentPrice_ = vehicle->totalShipmentPrice_ + (vehicle->regions_->size() * vehicle->shippingPrice_);
		vehicle->ordersIDs_->clear();
		vehicle->regions_->clear();
		vehicle->todayCarryCapacity_ = 0;
	}
}

void Firm::showCustomersInRegionWithTimePeriod(int region, Date &since, Date &to) {
	cout << "Name	" << "Firm profit	" << "Delivered: orders count, quantity(kg), profit" << "Canceled: orders count, quantity(kg), profit" << endl;

	for (Customer *customer : *customers_) {
		if (customer->address_ == region) {
			//double customerProfit = 0.0;

			//Delivered
			int deliveredCount = 0;
			int deliveredQuantity = 0;
			double deliveredProfit = 0;

			// Not delivered
			int notDeliveredCount = 0;
			int notDeliveredQuantity = 0;
			double notDeliveredProfit = 0;
			to.oneDayForward();
			for (Order *order : *orders_) {
				if (!to.isEqual(since)) {
					if (order->delivered_) {
						if (order->customerName_ == customer->name_) {
							deliveredCount++;
							deliveredQuantity = deliveredQuantity + order->quantity_;
							deliveredProfit = deliveredProfit + order->getFirmProfit();
						}
					}
					else // ak nebola dorucena
					{
						if (order->customerName_ == customer->name_) {
							notDeliveredCount++;
							notDeliveredQuantity = notDeliveredQuantity + order->quantity_;
							notDeliveredProfit = notDeliveredProfit + order->getFirmProfit();
						}
					}
				}
				since.oneDayForward();
			}
			cout << "Name: " << customer->name_ << endl
				<< "total profit: " << to_string(deliveredProfit) << endl // profit z dorucenych je zaroven aj celkovy profit zo zakaznika pre firmu
				<< "deliveredCount: " << deliveredCount << endl
				<< "deliveredQuantity: " << deliveredQuantity << endl
				<< "deliveredProfit: " << deliveredProfit << endl
				<< "notDeliveredCount: " << notDeliveredCount << endl
				<< "notDeliveredQuantity: " << notDeliveredQuantity << endl
				<< "notDeliveredProfit: " << notDeliveredProfit
				<< endl;
		}
	}
}

void Firm::showSuccessfulOrderInTimePeriod(Date & since, Date & to) {
	//bublesort 
	for (int j = 0; j < orders_->size() - 1; j++) {
		for (int i = 0; i < orders_->size() - 1; i++) {
			if (i + 1 <= orders_->size() - 1 && (*orders_)[i + 1]->deliveredDate_->isBigger(*(*orders_)[i]->deliveredDate_)) {
				Order *tmpOdred = (*orders_)[i];
				(*orders_)[i] = (*orders_)[i + 1];
				(*orders_)[i] = tmpOdred;
			}
		}
	}
	to.oneDayForward();
	for (Order *order : *orders_) {
		if (order->delivered_) {
			if (!since.isBigger(to)) {
				cout << order->deliveredDate_->toString() << " " << order->customerName_ << " " << (order->productType_ == FinalProductType::Fries ? "Fries " : "Chips ")
					<< order->quantity_ << " " << order->getFirmProfit() << endl;
			}
			since.oneDayForward();
		}
	}
}

void Firm::showUnsuccessfulOrderInTimePeriod(Date & since, Date & to) {
	//bublesort 
	for (int j = 0; j < orders_->size() - 1; j++) {
		for (int i = 0; i < orders_->size() - 1; i++) {
			if (i + 1 <= orders_->size() - 1 && (*orders_)[i + 1]->orderDate_->isBigger(*(*orders_)[i]->orderDate_)) {
				Order *tmpOdred = (*orders_)[i];
				(*orders_)[i] = (*orders_)[i + 1];
				(*orders_)[i] = tmpOdred;
			}
		}
	}

	cout << "Order date		" << "Customer	" << "Product type	" << "Quantity	" << "Lost profit" << endl;
	to.oneDayForward();
	for (Order *order : *orders_) {
		if (order->canceled_ || order->deniedOrder_) {
			if (!to.isEqual(since)) {
				cout << order->orderDate_->toString() << " " << order->customerName_ << " " << (order->productType_ == FinalProductType::Fries ? "Fries " : "Chips ")
					<< order->quantity_ << " " << order->getFirmProfit() << endl;
			}
			since.oneDayForward();
		}
	}
}

int Firm::getPotatoesStock()
{
	return potatoesStock_;
}

int Firm::getOilStock()
{
	return oilStock_;
}

int Firm::getFlavorsStock()
{
	return flavorsStock_;
}
