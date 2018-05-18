#pragma once

#include "Biofarmar.h"
#include "BiofarmProductType.h"
#include "Date.h"

class SemiProductOrder
{
public:
	SemiProductOrder();
	SemiProductOrder(string biofarmarName, Date &purchaseDate);
	~SemiProductOrder();

	string biofarmarName_;
	Date *purchaseDate_;
	BiofarmProductType type_;
	double price_;
	int quantity_;

};

