/*
 * strategy.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef FQ_STRATEGY_H
#define FQ_STRATEGY_H

#include <memory>
#include <string>
#include <vector>

namespace FreeQuant {

class Indicator;
class Rule;
class Signal;
class Portfolio;
class Exchange;
class Bar;
class Quote;
class Trade;
class Order;
class Position;

class Strategy {
public:
    explicit Strategy();
	virtual ~Strategy();
    Exchange &getExchange(std::string id);

    void onStart();
    void onExit();
    void onBar(const FreeQuant::Bar& bar);
    void onQuote(const FreeQuant::Quote& quote);
    void onTrade(const FreeQuant::Trade& trade);
    void onTask();
    void onOrderCreated(const FreeQuant::Order& order);
    void onOrderFilled(const FreeQuant::Order& order);
    void onOrderPartiallyFilled(const FreeQuant::Order& order);
    void onOrderCancelled(const FreeQuant::Order& order);
    void onOrderExpired(const FreeQuant::Order& order);
    void onOrderRejected(const FreeQuant::Order& order);
    void onOrderReplaced(const FreeQuant::Order& order);

    void onPositionOpened(const FreeQuant::Position& position);
    void onPositionClosed(const FreeQuant::Position& position);
    void onPositionValueChanged(const FreeQuant::Position& position);

    void addIndicator(const Indicator &indicator);

private:
	std::vector<Indicator *> mIndictors;
	std::vector<Signal *> mSignals;
	std::vector<Rule *> mRrules;
};

} /* namespace FreeQuant */

#endif /* FQ_STRATEGY_H */
