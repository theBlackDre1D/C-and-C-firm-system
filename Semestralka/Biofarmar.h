#pragma once

#include <string>
#include "structures\list\linked_list.h"
#include "structures\array\array.h"

using namespace structures;
using namespace std;

class Biofarmar {
public:
	Biofarmar();
	//Biofarmar(string name);
	Biofarmar(string name, int productType);
	~Biofarmar();

	string businessName_;
	//LinkedList<Product*> *products_;

	//double averagePricePotato_;
	//double averagePriceOil_;
	//double averagePriceFlavors_;

	bool hasPotatoes;
	bool hasOil;
	bool hasFlavors;
	int potatoPrice_;
	int potatoQuantity_;
	int oilQuantity_;
	int oilPrice_;
	int	flavorsPrice_;
	int flavorsQuantity_;
	void addProduct(int number);
	void setPriceForToday();
	//    bool isInProducts(const int number);

	int orderCount_;
	int pricesCount_;
	int count_;
	int kilosCount_;
private:
	//ArrayList<double> *allPricesPotato_;
	//ArrayList<double> *allPricesOil_;
	//ArrayList<double> *allPricesFlavor_;
};
