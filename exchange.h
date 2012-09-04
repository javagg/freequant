#ifndef EXCHANGE_H
#define EXCHANGE_H

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

}
#endif // EXCHANGE_H
