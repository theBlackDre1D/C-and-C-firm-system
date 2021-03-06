#include "stdafx.h"
#include "structures\heap_monitor.h"
#include "structures\list\array_list.h"
#include "Firm.h"
#include "BiofarmProductType.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

int main()
{
	string first = "aa";
	string second = "bz";
	if (first < second)
	{
		cout << "true";
	}
	initHeapMonitor();
	bool loopCondition = true;
	Firm *firm = new Firm();

	//Nacitavanie biofarmarov
	ifstream biofarmarsFile;
	biofarmarsFile.open("biofarmars.txt");
	string name;
	int productType;
	while (biofarmarsFile >> name >> productType)
	{
		Biofarmar *biofarmar = new Biofarmar(name, productType);
		firm->addBiofarmar(*biofarmar);
		biofarmar = nullptr;
	}
	// nacitavanie zakaznikov
	ifstream customersFile;
	customersFile.open("customers.txt");
	string customerName;
	int customerAddress;
	while (customersFile >> customerName >> customerAddress)
	{
		Customer *newCustomer = new Customer(customerName, customerAddress);
		firm->customers_->add(newCustomer);
		newCustomer = nullptr;
	}

	// nacitavanie vozidiel
	ifstream vehicleFile;
	vehicleFile.open("vehicles.txt");
	string SPZ;
	//int productType;
	while (vehicleFile >> SPZ >> productType)
	{
		//Vehicle *newVehicle = new Vehicle(SPZ, productType);
		//(*newVehicle->firstDay_) = (*firm->todayDate_);
		if (productType == 1)
		{
			firm->addVehicles(SPZ, FinalProductType::Fries);
		}
		else
		{
			firm->addVehicles(SPZ, FinalProductType::Chips);
		}
		
	}

	// nacitavanie objednavok
	ifstream ordersFile;
	ordersFile.open("orders.txt");
	int type, address, quantity, day_order, month_order, year_order, day_dispatch, month_dispatch, year_dispatch;
	//string name;
	while (ordersFile >> type >> quantity >> name >> address >> day_order >> month_order >> year_order >> day_dispatch >> month_dispatch >> year_dispatch)
	{
		Date *dispatchDate = new Date(day_dispatch, month_dispatch, year_dispatch);
		if (firm->todayDate_->differenceBetweenDates(*dispatchDate) > 7)
		{
			if (type == 1)
			{
				int index = 0;
				for (Customer *customer : *firm->customers_)
				{
					if (customer->name_ == name)
					{
						index = firm->customers_->getIndexOf(customer);
					}
				}
				//Date *dispatchDate = new Date(day_dispatch, month_dispatch, year_dispatch);
				Customer *customer = (*firm->customers_)[index];
				firm->createNewOrderAs(*customer, quantity, *dispatchDate, FinalProductType::Fries);
				delete dispatchDate;
			}
			else
			{
				int index = 0;
				for (Customer *customer : *firm->customers_)
				{
					if (customer->name_ == name)
					{
						index = firm->customers_->getIndexOf(customer);
					}
				}
				//Date *dispatchDate = new Date(day_dispatch, month_dispatch, year_dispatch);
				Customer *customer = (*firm->customers_)[index];
				firm->createNewOrderAs(*customer, quantity, *dispatchDate, FinalProductType::Chips);
				delete dispatchDate;
			}
		}
		else
		{
			cout << "First check Order was not accepted. You must make order at least 7 day before your dispatch day." << endl;
			delete dispatchDate;
		}
	}

	// nacitavanie objednavok od biofarmarov
	ifstream biofarmarsOrdersFile;
	biofarmarsOrdersFile.open("biofarmarsOrders.txt");
	//string name;
	int day, month, year, price;
	while (biofarmarsOrdersFile >> name >> type >> day >> month >> year >> price >> quantity)
	{
		Date *date = new Date(day, month, year);
		SemiProductOrder *newOrder = new SemiProductOrder(name, *date);
		newOrder->price_ = price;
		newOrder->quantity_ = quantity;
		if (type == 1)
		{
			newOrder->type_ = BiofarmProductType::Potato;
		} 
		else if (type == 2)
		{
			newOrder->type_ = BiofarmProductType::Oil;
		}
		else
		{
			newOrder->type_ = BiofarmProductType::Flavors;
		}
		firm->ordersFromBiofarmars_->add(newOrder);
		newOrder = nullptr;
		//delete date;
	}

	//cout << "Date:" << endl;
	//cout << firm->todayDate_->toString() << endl;

	cout << "Welcome in our firm system" << endl;
	cout << "You can do follwing: " << endl
		<< "1 -> add Biofarmar" << endl
		<< "2 -> add Vehicle" << endl
		<< "3 -> add product to biofarmar" << endl
		<< "4 -> show Biofarmars With Product" << endl
		<< "5 -> show firm's vehicles" << endl
		<< "6 -> create New Order" << endl
		<< "7 -> check Stock" << endl
		<< "8 -> show Orders For Tomorrow" << endl
		<< "9 -> add Customer" << endl
		<< "10 -> go one day forward" << endl
		<< "11 -> show customers in region" << endl
		<< "12 -> show successfully delivered orders in some time period" << endl
		<< "13 -> show unsuccessfully delivered orders in some time period" << endl
		<< "14 -> deliver the goods to customers" << endl
		<< "15 -> show today date" << endl
		<< "16 -> refill stock" << endl
		//<< "17 -> create order from biofarmar" << endl
		<< "17 -> show stock" << endl
		<< "18 -> save firm state to file" << endl
		<< endl
		<< "112 - terminate whole program." << endl
		<< "===========================================" << endl
		<< endl;

	while (loopCondition) {
		
		int input;
		cout << "Insert number acording to desired function: ";
		cin >> input;
		switch (input) {
		case 112: {
			loopCondition = false;
			break;
		}
		case 1: { // adding biofarmar
			cout << "Enter biofarmar name:" << endl;
			string inputName;
			cin >> inputName;
			cout << "Choose product for biofarmar 1 = potatoes, 2 = oil, 3 = flavors" << endl;
			int productType;
			cin >> productType;
			Biofarmar *newFarmar = new Biofarmar(inputName, productType);
			firm->addBiofarmar(dynamic_cast<Biofarmar &>(*newFarmar));
			break;
		}


		case 2: { // adding new vehicle
			cout << "Enter SPZ:" << endl;
			string SPZ;
			cin >> SPZ;

			cout << "Enter product for vehicle: 1 = Fries, 2 = Chips" << endl;
			int vehicleType;
			cin >> vehicleType;
			if (vehicleType == 1) {
				firm->addVehicles(SPZ, FinalProductType::Fries);
			}
			else if (vehicleType == 2)
			{
				firm->addVehicles(SPZ, FinalProductType::Chips);
			}
			else
			{
				cout << "You inserted wrong number - try again" << endl;
			}

			break;
		}

		case 3:
		{
			int index = 1;
			for (Biofarmar *biofarmar : *firm->biofarmars_)
			{
				cout << index << " -> " << biofarmar->businessName_ << " " << (biofarmar->hasPotatoes ? "Potatoes " : " ")
					<< (biofarmar->hasOil ? "Oil " : " ") << (biofarmar->hasFlavors ? "Flavors" : " ") << endl;
				index++;
			}
			cout << "Insert number acording to biofarmar you wish to modify " << endl;
			int biofarmarNumber;
			cin >> biofarmarNumber;
			cout << "Insert product number 1 = Potatoes, 2 = Oil, 3 = Flavors" << endl;
			int productNumber;
			cin >> productNumber;
			Biofarmar *biofarmar = (*firm->biofarmars_)[biofarmarNumber - 1];
			firm->addProductToBiofarmar(productNumber, biofarmar);
			break;
		}

		case 4: {
			cout << "Enter product: 1 = potatoes, 2 = oil, 3 = flavors. " << endl;
			int number;
			cin >> number;
			firm->showBiofarmarsWithProduct(number);
			break;
		}

		case 5: {
			firm->showVehicles();
			break;
		}

		case 6: {
			if (firm->customers_->size() == 0) {
				cout << "We have no customers please register and try create order again" << endl;
				break;
			}
			else
			{
				cout << "For create order you have to login as one of existing customer. " << endl
					<< "Pick desired customer by number." << endl;
				int count = 1;
				for (Customer *customer : *firm->customers_) {
					cout << count << " " << customer->name_ << endl;
					count++;
				}

				int pickedFarberNumber;
				cin >> pickedFarberNumber;
				Customer *pickedCustomer = (*firm->customers_)[pickedFarberNumber - 1];

				cout << "Pick type of product: 1 = Fries, 2 = Chips " << endl;
				int typeNumber;
				cin >> typeNumber;

				cout << "Enter quantity " << endl;
				int desiredQuantity;
				cin >> desiredQuantity;

				cout << "You will be creating dispatch date by adding first day, month and year. " << endl;
				cout << "Day: ";
				int day;
				cin >> day;
				cout << "Month: ";
				int month;
				cin >> month;
				cout << "Year: ";
				int year;
				cin >> year;
				Date *newDispatchDate = new Date(day, month, year);
				if (firm->todayDate_->differenceBetweenDates(*newDispatchDate) > 7)
				{
					cout << "Order was not accepted. You must make order at least 7 day before your dispatch day." << endl;
					break;
				}
				//int latestOrderID = (*firm->orders_)[firm->orders_->size() - 1]->ID_;
				if (typeNumber == 1) {
					firm->createNewOrderAs(*pickedCustomer, desiredQuantity, *newDispatchDate, FinalProductType::Fries);
				}
				else
				{
					firm->createNewOrderAs(*pickedCustomer, desiredQuantity, *newDispatchDate, FinalProductType::Chips);
				}
				delete newDispatchDate;
			}
			break;
		}

		case 7: {
			firm->checkStock();
			cout << endl << "Stock was checked and refilled in case of need." << endl;
			break;
		}

		case 8: {
			firm->showOrdersForTomorrow();
			break;
		}

		case 9: {
			cout << "Enter name: " << endl;
			string enteredName;
			cin >> enteredName;
			transform(enteredName.begin(), enteredName.end(), enteredName.begin(), ::toupper); // premeni mi na velke pismena

			cout << "Enter address by integer value from 1 - 8: " << endl;
			int enteredAddress;
			cin >> enteredAddress;

			Customer *newCustomer = new Customer(enteredName, enteredAddress);
			firm->addCustomer(*newCustomer);
			break;
		}

		case 10: {
			firm->goToTheNextDay();
			break;
		}

		case 11: {
			cout << "Enter region number (1 - 8) ";
			int regionNubmer;
			cin >> regionNubmer;

			cout << "Now you will enter date SINCE you want to show details and then date TO." << endl;
			cout << "Enter day ";
			int sinceDay;
			cin >> sinceDay;
			cout << endl;

			cout << "Enter month: ";
			int sinceMonth;
			cin >> sinceMonth;
			cout << endl;

			cout << "Enter year: ";
			int sinceYear;
			cin >> sinceYear;

			cout << "Now you'll enter second date." << endl;
			cout << "Enter day: ";
			int toDay;
			cin >> toDay;
			cout << endl;

			cout << "Enter month: ";
			int toMonth;
			cin >> toMonth;
			cout << endl;

			cout << "Enter year: ";
			int toYear;
			cin >> toYear;

			Date *since = new Date(sinceDay, sinceMonth, sinceYear);
			Date *to = new Date(toDay, toMonth, toYear);

			firm->showCustomersInRegionWithTimePeriod(regionNubmer, *since, *to);
			break;
		}

		case 12: { // success orders
			cout << "Now you will enter date SINCE you want to show details and then date TO." << endl;
			cout << "Enter day ";
			int sinceDay;
			cin >> sinceDay;
			cout << endl;

			cout << "Enter month: ";
			int sinceMonth;
			cin >> sinceMonth;
			cout << endl;

			cout << "Enter year: ";
			int sinceYear;
			cin >> sinceYear;

			cout << "Now you'll enter second date." << endl;
			cout << "Enter day: ";
			int toDay;
			cin >> toDay;
			cout << endl;

			cout << "Enter month: ";
			int toMonth;
			cin >> toMonth;
			cout << endl;

			cout << "Enter year: ";
			int toYear;
			cin >> toYear;

			Date *since = new Date(sinceDay, sinceMonth, sinceYear);
			Date *to = new Date(toDay, toMonth, toYear);
			firm->showSuccessfulOrderInTimePeriod(*since, *to);
			break;
		}

		case 13: {
			cout << "Now you will enter date SINCE you want to show details and then date TO." << endl;
			cout << "Enter day ";
			int sinceDay;
			cin >> sinceDay;
			cout << endl;

			cout << "Enter month: ";
			int sinceMonth;
			cin >> sinceMonth;
			cout << endl;

			cout << "Enter year: ";
			int sinceYear;
			cin >> sinceYear;

			cout << "Now you'll enter second date." << endl;
			cout << "Enter day: ";
			int toDay;
			cin >> toDay;
			cout << endl;

			cout << "Enter month: ";
			int toMonth;
			cin >> toMonth;
			cout << endl;

			cout << "Enter year: ";
			int toYear;
			cin >> toYear;

			Date *since = new Date(sinceDay, sinceMonth, sinceYear);
			Date *to = new Date(toDay, toMonth, toYear);
			firm->showUnsuccessfulOrderInTimePeriod(*since, *to);
			break;
		}

		case 14: {
			firm->deliverGoods();
			break;
		}
		case 15: {
			cout << firm->todayDate_->toString();
			break;
		}

		case 16: {
			firm->checkStock();
			break;
		}

		case 17:
		{
			cout << "Potatoes: " << firm->getPotatoesStock() << endl
				<< "Oil: " << firm->getOilStock() << endl
				<< "Flavors: " << firm->getFlavorsStock() << endl;
			break;
		}

		case 18:
		{
			firm->saveStateOfFirmToFile();
			break;
		}
		default: 
			break;
		}
	}
	delete firm;
	firm = nullptr;
	return 0;
}

