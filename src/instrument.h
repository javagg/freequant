/*
 * Instrument.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>

namespace FreeQuant {

class Currency;

class Instrument {
public:
    enum Type {
        Stock,
        Future,
        Option,
        FutureOption,
        Bond,
        Index,
        ETF,
        Forex,
        MultiLeg
    };

	explicit Instrument(std::string id);
	virtual ~Instrument();

	std::string getId() const;
private:
	std::string mId;
	Currency *mCurrency;
	double mMultiplier;
	double mTickSize;
};

} /* namespace FreeQuant */

#endif /* INSTRUMENT_H */
