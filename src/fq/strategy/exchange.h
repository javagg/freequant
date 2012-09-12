#ifndef FQ_STRATEGY_EXCHANGE_H
#define FQ_STRATEGY_EXCHANGE_H

#include <string>

namespace FreeQuant { namespace Strategy {

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

}}

#endif // FQ_STRATEGY_EXCHANGE_H
