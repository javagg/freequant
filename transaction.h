/*
 * transaction.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

namespace FreeQuant {

class Transaction {
public:
	Transaction();
	virtual ~Transaction();

    double cost();
    double pnl();
    double qty();
    double price();
};

} /* namespace Bw */
#endif /* TRANSACTION_H */
