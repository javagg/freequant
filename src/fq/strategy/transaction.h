/*
 * transaction.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef FQ_STRATEGY_TRANSACTION_H
#define FQ_STRATEGY_TRANSACTION_H

namespace FreeQuant { namespace Strategy {

class Transaction {
public:
	Transaction();
	virtual ~Transaction();

    double cost();
    double pnl();
    double qty();
    double price();
};

}} /* namespace Bw */

#endif /* FQ_STRATEGY_TRANSACTION_H */
