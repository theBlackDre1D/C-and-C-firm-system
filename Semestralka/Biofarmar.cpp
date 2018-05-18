
#include <iostream>
#include <random>

#include "Biofarmar.h"
#include "BiofarmProductType.h"
//#include "structures\list\array_list.h"
#include "Product.h"

using namespace structures;

Biofarmar::Biofarmar() {

}

Biofarmar::Biofarmar(string name, int productType) {
	businessName_ = name;
	hasFlavors = false;
	hasOil = false;
	hasPotatoes = false;
	//products_ = new LinkedList<Product*>();


	std::mt19937 rand;
	rand.seed(std::random_device{}());
	if (productType == 1) {
		hasPotatoes = true;
		std::uniform_int_distribution<int> quantityRange(0, 5000);
		std::uniform_int_distribution<int> priceRange(1, 3);
		int quantity = quantityRange(rand);
		int price = priceRange(rand);

		potatoPrice_ = price;
		potatoQuantity_ = quantity;
	}
	else if (productType == 2) {
		hasOil = true;
		std::uniform_int_distribution<int> quantityRange(0, 1000);
		std::uniform_int_distribution<int> priceRange(1, 4);
		int quantity = quantityRange(rand);
		int price = priceRange(rand);
		oilPrice_ = price;
		oilQuantity_ = quantity;
	}
	else {
		hasFlavors = true;
		std::uniform_int_distribution<int> quantityRange(0, 50); // 50 000g = 50 kg
		std::uniform_int_distribution<int> priceRange(1, 2);
		int quantity = quantityRange(rand);
		int price = priceRange(rand);
		flavorsPrice_ = price;
		flavorsQuantity_ = quantity;
	}
	count_ = 0;
	kilosCount_ = 0;
	orderCount_ = 0;
	pricesCount_ = 0;
}

Biofarmar::~Biofarmar() {

}

void Biofarmar::addProduct(int productType) {
	std::mt19937 rand;
	rand.seed(std::random_device{}());
	if (productType == 1 && hasPotatoes == false) {
		hasPotatoes = true;
		std::uniform_int_distribution<int> quantityRange(0, 5000);
		std::uniform_int_distribution<int> priceRange(1, 3);
		int quantity = quantityRange(rand);
		int price = priceRange(rand);
		potatoPrice_ = price;
		potatoQuantity_ = quantity;
	}
	else if (productType == 2 && hasOil == false) {
		hasOil = true;
		std::uniform_int_distribution<int> quantityRange(0, 1000);
		std::uniform_int_distribution<int> priceRange(1, 4);
		int quantity = quantityRange(rand);
		int price = priceRange(rand);
		oilPrice_ = price;
		oilQuantity_ = quantity;
	}
	else if (productType == 3 && hasFlavors == false){
		hasFlavors = true;
		std::uniform_int_distribution<int> quantityRange(0, 50);
		std::uniform_int_distribution<int> priceRange(1, 2);
		int quantity = quantityRange(rand);
		int price = priceRange(rand);
		flavorsPrice_ = price;
		flavorsQuantity_ = quantity;
	}
	else
	{
		cout << "Biofarmar already have this type of product!" << endl;
	}
}

void Biofarmar::setPriceForToday() {
	std::mt19937 rand;
	rand.seed(std::random_device{}());
	if (hasPotatoes) {
		std::uniform_int_distribution<int> quantityRangePotato(0, 5000);
		std::uniform_int_distribution<int> priceRangePotato(1, 3);
		potatoQuantity_ = quantityRangePotato(rand);
		potatoPrice_ = priceRangePotato(rand);
	}
	if (hasOil) {
		std::uniform_int_distribution<int> quantityRangeOil(0, 1000);
		std::uniform_int_distribution<int> priceRangeOil(1, 4);
		oilQuantity_ = quantityRangeOil(rand);
		oilPrice_ = priceRangeOil(rand);
	}
	if (hasFlavors) {
		std::uniform_int_distribution<int> quantityRangeFlavors(0, 50);
		std::uniform_int_distribution<int> priceRangeFlavors(1, 2);
		flavorsQuantity_ = quantityRangeFlavors(rand);
		flavorsPrice_ = priceRangeFlavors(rand);
	}
}