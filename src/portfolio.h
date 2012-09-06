/*
 * Portfolio.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <vector>

namespace FreeQuant {

class Instrument;
class Currency;

class Portfolio {

private:
	std::vector<Instrument*> mInstruments;
	Currency *mCurrency;
};

} /* namespace FreeQuant */
#endif /* PORTFOLIO_H_ */
