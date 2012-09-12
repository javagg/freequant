/*
 * Stock.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef FQ_STRATEGY_STOCK_H
#define FQ_STRATEGY_STOCK_H

#include "instrument.h"

namespace FreeQuant { namespace Strategy {

class Stock: public Instrument {
public:
	explicit Stock();
	virtual ~Stock();
};

}} /* namespace Bw */

#endif /* FQ_STRATEGY_STOCK_H */
