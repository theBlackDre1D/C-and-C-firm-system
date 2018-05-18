//
// Created by Michal Gaborik on 15.3.18.
//

#include "Product.h"

Product::Product() {
	type_ = BiofarmProductType::Flavors; //
	price_ = 0;
	quantity_ = 0;
}

Product::~Product() {

}

Product::Product(const int typeNumber, const float price) { // my custom constructor
	if (typeNumber == 1) {
		type_ = BiofarmProductType::Potato;
	}
	else if (typeNumber == 2) {
		type_ = BiofarmProductType::Oil;
	}
	else {
		type_ = BiofarmProductType::Flavors;
	}
	price_ = price;
}