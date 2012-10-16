#ifndef FQ_STRATEGY_EXCHANGE_H
#define FQ_STRATEGY_EXCHANGE_H

#include <string>

namespace FreeQuant {

class Exchange
{
public:
    Exchange();
    std::string openTime();
    std::string closeTime();

private:
    std::string mOpenTime;
    std::string mCloseTime;
};

} // namespace FreeQuant

#endif // FQ_STRATEGY_EXCHANGE_H
