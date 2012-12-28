#ifndef FQ_FIX_MESSAGEFACTORY_H
#define FQ_FIX_MESSAGEFACTORY_H

#include <quickfix/MessageCracker.h>

namespace FreeQuant {

class Order;
class Trade;
class Tick;
class Bar;
class Position;
class Account;

class MessageFactory {
public:
    static void messageFrom(const FIX44::NewOrderSingle&, Order&);
    static void toMessage(const Order&, FIX44::NewOrderSingle&);
};

}

#endif // MESSAGEFACTORY
