#pragma once

#include <string>
#include "FinalProductType.h"


using namespace std;
class Customer {
public:
	Customer();
	Customer(string name, int address);
	~Customer();

	string name_;
	int address_; // number of region
	
private:
};