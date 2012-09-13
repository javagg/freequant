/*
 * order.h
 *
 *  Created on: 2012-7-1
 *      Author: alex
 */

#ifndef FQ_STRATEGY_ORDER_H
#define FQ_STRATEGY_ORDER_H

#include <fq/trade/tradeprovider.h>

namespace FreeQuant { namespace Strategy {

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
    double price();
    double qty();
    void side();

    typedef FreeQuant::Trade::TradeProvider TradeProvider;
    TradeProvider *tradeProvider() const;
private:
    TradeProvider *m_tradeProvider;
};

}} /* namespace FreeQuant */

#endif /* FQ_STRATEGY_ */
