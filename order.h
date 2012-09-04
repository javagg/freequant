/*
 * order.h
 *
 *  Created on: 2012-7-1
 *      Author: alex
 */

#ifndef ORDER_H_
#define ORDER_H_

namespace xt {

class Order {
public:
    enum OrderSide { Buy , Sell };

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
         Rejected
    };
	Order();
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


};

} /* namespace xt */
#endif /* ORDER_H_ */
