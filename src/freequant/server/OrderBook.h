#ifndef FQ_SERVER_ORDERBOOK_H
#define FQ_SERVER_ORDERBOOK_H

#include <list>

namespace FreeQuant {

class Offer {};
class Bid {};
class Fill {};

class OrderBook {
public:
	virtual ~OrderBook();
private:
    std::list<Offer> offers;
    std::list<Bid> bids;
    std::list<Fill> trades;
};

} // namespace FreeQuant

#endif // FQ_SERVER_ORDERBOOK_H
