/*
 * Stock.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef STOCK_H
#define STOCK_H

#include "instrument.h"

namespace FreeQuant {

class Stock: public Instrument {
public:
	explicit Stock();
	virtual ~Stock();
};

} /* namespace Bw */

#endif /* STOCK_H */
