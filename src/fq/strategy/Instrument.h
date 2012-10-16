#ifndef FQ_STRATEGY_INSTRUMENT_H
#define FQ_STRATEGY_INSTRUMENT_H

#include <string>

#include <fq/utils/datetime.h>

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

    explicit Instrument(std::string symbol);
    virtual ~Instrument() {}
    double multipler() const;
    double margin() const;
    double tickSize() const;
    std::string symbol() const { return _symbol; }
    Type type() const { return _type; }
    double factor() const;
    std::string description() const;
    FreeQuant::Utils::DateTime maturity() const;

private:
    std::string _symbol;
    Type _type;
	Currency *mCurrency;
	double mMultiplier;
	double mTickSize;
};

}} /* namespace FreeQuant */

#endif /* FQ_STRATEGY_INSTRUMENT_H */
