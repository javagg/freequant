/*
 * Instrument.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>

namespace xh {

class Currency;

class Instrument {
public:
	explicit Instrument(std::string id);
	virtual ~Instrument();

	std::string getId() const;
private:
	std::string mId;
	Currency *mCurrency;
	double mMultiplier;
	double mTickSize;
};

} /* namespace Bw */

#endif /* INSTRUMENT_H */
