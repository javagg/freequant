#ifndef FQ_SERVER_ORDERBOOK_H
#define FQ_SERVER_ORDERBOOK_H

#include <list>
#include <string>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace FreeQuant {

class Order;
class Bar;
class Offer {};
class Bid {};
class Fill {};

class OrderBook {
public:
    OrderBook(std::string symbol) : _symbol(symbol) {}
	virtual ~OrderBook();

    std::string symbol() const;
    bool insertOrder(FreeQuant::Order& order);
    bool removeOrder(FreeQuant::Order& order);
    bool match(FreeQuant::Order& bid, FreeQuant::Order& ask);
    bool findOrder(FreeQuant::Order& order);

    Bar queryMarketData();
    void processOrders();

private:
    std::string _symbol;
    std::list<Offer> offers;
    std::list<Bid> bids;
    std::list<Fill> trades;

    boost::thread _thread;
    boost::mutex _mutex;
};

} // namespace FreeQuant

#endif // FQ_SERVER_ORDERBOOK_H
