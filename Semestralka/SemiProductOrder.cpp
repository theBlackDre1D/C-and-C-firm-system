#include "SemiProductOrder.h"
#include <string>



SemiProductOrder::SemiProductOrder()
{
	
}

SemiProductOrder::SemiProductOrder(string biofarmarName, Date & purchaseDate)
{
	biofarmarName_ = biofarmarName;
	purchaseDate_ = &purchaseDate;
}


SemiProductOrder::~SemiProductOrder()
{
	delete purchaseDate_;
}
