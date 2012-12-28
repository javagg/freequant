#ifndef FQ_STRATEGY_ORDER_H
#define FQ_STRATEGY_ORDER_H

#include <freequant/utils/DateTime.h>
#include <freequant/Exception.h>

namespace FreeQuant {

class TradeProvider;

class Order {
public:
    typedef std::string OrderId;
    enum OrderType {
        Market,
        Limit,
        LimitOnClose,
        Stop,
        StopLoss,
        StopLimit,
        Trail,
        TrailLimit,
        TrailingStop,
        MarketOnOpen,
        MarketOnClose
    };

    enum Side { Buy , Sell };

    enum TimeInForce { DAY, GTC, OPG, IOC, FOK, GTX, GTD, ATC, GFS };

    enum OrderStatus {
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

    enum OrderCapacity {
        Unknown,
        Agency,
        Proprietary,
        Individual,
        Principal,
        RisklessPrincipal,
        AgentOtherMember
    };

    enum StopMode { Absolute, Percent };
    enum StopType { Fixed, Trailing, Timed };

    explicit Order();
    explicit Order(const std::string& symbol, OrderType type, Side side, double price, long qty);
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

    const OrderId& orderId() const { return _id; }
    OrderType type() const { return _type; }
    void setType(OrderType type) { _type = type; }
    const std::string& symbol() const { return _symbol; }
    double price() const { return _price; }
    double qty() const { return _qty; }
    double tickSize() const { return _tickSize; }
    Side side() const { return _side; }
    void setSide(Side side) { _side = side; }
    OrderStatus status() const { return _status; }

    /*!
     *  Gets last fill (partial fill) price for this order
     * \brief lastPrice
     */
    double lastPrice() const { return 0; }
    /*!
     *  Gets last fill (partial fill) quantity for this order
     * \brief lastPrice
     */
    long lastQty() const { return 0; }
    /*!
     *  Gets average fill price for this order
     * \brief avgPrice
     * \return
     */

    long remainingQty() const { return 0; }
    double avgPrice() const { return _avgPrice; }

    /*!
     *  Gets cumulative filled quantity for this order
     * \brief cumQty
     * \return
     */
    double cumQty() const { return 0; }

    const DateTime& dateTime() const {}
    const DateTime& expireTime() const {}
    double stopPrice() const { return _stopPrice; }
    double limitPrice() const { return _limitPrice; }
    std::string currency() const { return _currency; }
    TimeInForce timeInForce() const { return _timeInForce; }
    FreeQuant::TradeProvider *tradeProvider() const;
    std::string brokerId;

private:
    OrderId _id;
    OrderType _type;
    std::string _symbol;
    std::string _currency;
    double _price;
    double _qty;
    double _tickSize;
    double _stopPrice;
    double _limitPrice;
    double _avgPrice;
    Side _side;
    OrderStatus _status;
    TimeInForce _timeInForce;
};

} // namespace FreeQuant

#endif /* FQ_STRATEGY_ */
