#pragma once
#include <string>
#include "BiofarmProductType.h"


class Product {
public:
	Product();
	explicit Product(int typeNumber, float price);
	~Product();

	BiofarmProductType type_;
	int price_;
	int quantity_;

	//    BiofarmProductType getType();

private:
};