#ifndef FQ_STRATEGY_ORDER_H
#define FQ_STRATEGY_ORDER_H

#include <freequant/trade/TradeProvider.h>

namespace FreeQuant {

class Order {
public:
    enum Type {
        Market,
        Limit,
        Stop,
        StopLimit,
        StopTrailing
    };

    enum Side { Buy , Sell };

    enum Status {
        PendingNew,
        New,
        PartiallyFilled,
        Filled,
        PendingCancel,
        Cancelled,
        Expired,
        PendingReplace,
        Replaced,
        Rejected
    };

    explicit Order();
	virtual ~Order();

    void cancel();
    void replace();
    void send();

    bool isFilled();
    bool isRejected();
    bool isNew();
    bool isExpired();
    bool isPartiallyFilled();
    bool isCancelled();
    bool isPendingNew();
    bool isPendingReplace();
    double price() { return _price; }
    double qty() { return _qty; }
    double tickSize() { return _tickSize; }
    void side();

    double stopPrice() { return _stopPrice; }
    double limitPrice() { return _limitPrice; }
//    typedef FreeQuant::Trade::TradeProvider TradeProvider;
    FreeQuant::TradeProvider *tradeProvider() const;
    std::string brokerId;
    std::string instrument;

private:
    double _price;
    double _qty;
    double _tickSize;
    double _stopPrice;
    double _limitPrice;
    FreeQuant::TradeProvider *m_tradeProvider;
};

} // namespace FreeQuant

#endif /* FQ_STRATEGY_ */
