#include "OrderBook.h"

#include <freequant/marketdata/Quote.h>
#include <freequant/strategy/Order.h>

namespace FreeQuant {

bool OrderBook::insertOrder(FreeQuant::Order& order) {
    if (!isOrderValid()) return false;

    auto side = order.side();
    if (side == FreeQuant::Order::Buy) {
        auto type = order.type();
        switch (type) {
        case FreeQuant::Order::Market:
            double orderPx = order.price();
            long orderQty = order.qty();
            auto quote = lastQuote();
            double ask = lastQuote().ask();
            double txnPx = std::max(orderPx, ask);
            long txnQty = orderQty;
//            Trade trade;
//            _tradeSeries.append();
        default:
            break;
        }

    } else if (side== FreeQuant::Order::Sell) {

    }
}

bool OrderBook::isOrderValid(FreeQuant::Order& order) {
    return order.symbol() == symbol();
}

} // namespace FreeQuant
