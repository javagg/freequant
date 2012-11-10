#ifndef FQ_STRATEGY_ORDER_H
#define FQ_STRATEGY_ORDER_H

#include <freequant/utils/DateTime.h>
#include <freequant/Exception.h>

namespace FreeQuant {

class TradeProvider;

class Order {
public:
    typedef std::string OrderId;
    enum Type {
        Market,
        Limit,
        Stop,
        StopLoss,
        StopLimit,
        Trail,
        TrailLimit,
        MarketOnClose
    };

    enum Side { Buy , Sell };

    enum TimeInForce { DAY, GTC, OPG, IOC, FOK, GTX, GTD, ATC, GFS };

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
        Rejected,
        Suspended
    };

    explicit Order();
	virtual ~Order();

    /*!
     *  Sent a cancel request to a broker.
     */

    bool isFilled();
    bool isRejected();
    bool isNew();
    bool isExpired();
    bool isDone() { return isFilled() || isRejected() || isExpired(); }
    bool isPartiallyFilled();
    bool isCancelled();
    bool isPendingNew();
    bool isPendingReplace();

    OrderId orderId() const;
    Type type() const { return _type; }
    void setType(Type type) throw (FreeQuant::OrderTypeNotSupport&);
    std::string symbol() { return _symbol; }
    double price() { return _price; }
    double qty() { return _qty; }
    double tickSize() { return _tickSize; }
    Side side() const { return _side; }
    Status status() { return _status; }
    /*!
     *  Gets last fill (partial fill) price for this order
     * \brief lastPrice
     */
    double lastPrice() { return 0; }
    /*!
     *  Gets last fill (partial fill) quantity for this order
     * \brief lastPrice
     */
    long lastQty() { return 0; }
    /*!
     *  Gets average fill price for this order
     * \brief avgPrice
     * \return
     */

    long remainingQty() { return 0; }
    double avgPrice() { return _avgPrice; }

    /*!
     *  Gets cumulative filled quantity for this order
     * \brief cumQty
     * \return
     */
    double cumQty() { return 0; }

    const FreeQuant::DateTime& dateTime() {}
    const FreeQuant::DateTime& expireTime() {}
    double stopPrice() { return _stopPrice; }
    double limitPrice() { return _limitPrice; }
    std::string currency() { return _currency; }
    TimeInForce timeInForce() { return _timeInForce; }
    FreeQuant::TradeProvider *tradeProvider() const;
    std::string brokerId;
private:
    Type _type;
    std::string _symbol;
    std::string _currency;
    double _price;
    double _qty;
    double _tickSize;
    double _stopPrice;
    double _limitPrice;
    double _avgPrice;
    Side _side;
    Status _status;
    TimeInForce _timeInForce;
};

} // namespace FreeQuant

#endif /* FQ_STRATEGY_ */
