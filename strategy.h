/*
 * strategy.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <memory>
#include <string>
#include <vector>

namespace xh {

class Indicator;
class Rule;
class Signal;
class Portfolio;

class Strategy {
public:
	Strategy();
	virtual ~Strategy();

private:
	std::vector<Indicator *> mIndictors;
	std::vector<Signal *> mSignals;
	std::vector<Rule *> mRrules;
	std::shared_ptr<Portfolio> mPortfolio;

};

} /* namespace Bw */

#endif /* STRATEGY_H_ */
