/*
 * Instrument.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef FQ_STRATEGY_INSTRUMENT_H
#define FQ_STRATEGY_INSTRUMENT_H

#include <string>

namespace FreeQuant { namespace Strategy {

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
    double multipler() const;
    double margin() const;
    double tickSize() const;
    std::string symbol() const;
	std::string getId() const;
private:
	std::string mId;
	Currency *mCurrency;
	double mMultiplier;
	double mTickSize;
};

}} /* namespace FreeQuant */

#endif /* FQ_STRATEGY_INSTRUMENT_H */
