#ifndef FQ_UTILS_MARKETDATAGENERATOR_H
#define FQ_UTILS_MARKETDATAGENERATOR_H

#include <boost/signals2.hpp>

#include <freequant/marketdata/Bar.h>

namespace FreeQuant {

class MarketDataGenerator {
public:
    virtual ~MarketDataGenerator() {}
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual std::vector<std::string> availableSymbols() const = 0;
    void connect(std::function<void(const FreeQuant::Bar&)> func) {
        _onGenerated.connect(func);
    }
protected:
    typedef boost::signals2::signal<void(const FreeQuant::Bar&)> OnGenerated;
    OnGenerated _onGenerated;
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
