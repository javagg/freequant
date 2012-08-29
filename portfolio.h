/*
 * Portfolio.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <vector>

namespace xh {

class Instrument;
class Currency;

class Portfolio {

private:
	std::vector<Instrument*> mInstruments;
	Currency *mCurrency;
};

} /* namespace Bw */
#endif /* PORTFOLIO_H_ */
