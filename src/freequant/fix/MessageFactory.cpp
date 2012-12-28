#include "MessageFactory.h"

#include <quickfix/fix44/NewOrderSingle.h>

#include <freequant/strategy/Order.h>

#include <ThostFtdcTraderApi.h>

namespace FreeQuant {

void MessageFactory::messageFrom(const FIX44::NewOrderSingle& message, Order& order) {
    CThostFtdcInputOrderField field = {};
    FIX::Side side;
    message.get(side);
//    order.setSide(side);

    FIX::OrdType orderType;
    message.get(orderType);
//    order.setType(orderType);
}

void MessageFactory::toMessage(const Order& order, FIX44::NewOrderSingle& message) {

}

}
