/*
 * account.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>


namespace xh {

class Portfolio;
class Currency;

class Account {
public:
	explicit Account();
	virtual ~Account();

private:
    std::vector<Portfolio *> mPortfolios;
	Currency *mCurrency;
	double mQuantity;
	//"Additions", "Withdrawals",  "Realized.PL", "Unrealized.PL", "Int.Income", "Gross.Trading.PL",
  //  "Txn.Fees", "Net.Trading.PL", "Advisory.Fees", "Net.Performance",  "End.Eq"
};

} /* namespace Bw */
#endif /* ACCOUNT_H */
