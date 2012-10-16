#ifndef FQ_UTILS_MARKETDATAGENERATOR_H
#define FQ_UTILS_MARKETDATAGENERATOR_H

namespace FreeQuant {

class MarketDataGenerator {
public:
    virtual ~MarketDataGenerator() {}
    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace FreeQuant

#endif // FQ_UTILS_MARKETDATAGENERATOR_H
