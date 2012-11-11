#ifndef FQ_SERVER_ORDERBOOK_H
#define FQ_SERVER_ORDERBOOK_H

#include <list>
#include <string>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include <freequant/marketdata/Trade.h>
#include <freequant/utils/TimeSeries.h>

namespace FreeQuant {


class Quote;
class Order;
class Offer {};
class Bid {};
class Fill {};

class OrderBook {
public:
    OrderBook() {}
    OrderBook(std::string symbol) : _symbol(symbol) {}
    virtual ~OrderBook() {}

    std::string symbol() const;
    bool insertOrder(FreeQuant::Order& order);
    bool removeOrder(FreeQuant::Order& order);
    bool match(FreeQuant::Order& bid, FreeQuant::Order& ask);
    bool findOrder(FreeQuant::Order& order);

    const FreeQuant::Quote& lastQuote() const;
    void processOrders();

private:
    bool isOrderValid(FreeQuant::Order& order);
    int _barSeries;
    std::string _symbol;
    std::list<Offer> offers;
    std::list<Bid> bids;
    std::list<Fill> trades;

    TimeSeries<Trade> _tradeSeries;
    boost::thread _thread;
    boost::mutex _mutex;
};

} // namespace FreeQuant

#endif // FQ_SERVER_ORDERBOOK_H
