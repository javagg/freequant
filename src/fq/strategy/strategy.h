/*
 * strategy.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef FQ_STRATEGY_STRATEGY_H
#define FQ_STRATEGY_STRATEGY_H

#include <memory>
#include <string>
#include <vector>

#include <boost/asio/signal_set.hpp>

#include <fq/marketdata/bar.h>
#include <fq/marketdata/quote.h>

namespace FreeQuant { namespace Strategy {

class Indicator;
class Rule;
class Portfolio;
class Exchange;
class Trade;
class Order;
class Position;

class Strategy {
public:
    explicit Strategy();
	virtual ~Strategy();
    Exchange &getExchange(std::string id);

    void onInit();
    void onExit();
    void onStart();
    void onStop();
    void onBar(const FreeQuant::MarketData::Bar& bar);
    void onQuote(const FreeQuant::MarketData::Quote& quote);
    void onTrade(const Trade& trade);
    void onTask();
    void onOrderCreated(const Order& order);
    void onOrderFilled(const Order& order);
    void onOrderPartiallyFilled(const Order& order);
    void onOrderCancelled(const Order& order);
    void onOrderExpired(const Order& order);
    void onOrderRejected(const Order& order);
    void onOrderReplaced(const Order& order);

    void onPositionOpened(const Position& position);
    void onPositionClosed(const Position& position);
    void onPositionValueChanged(const Position& position);

    void addIndicator(const Indicator &indicator);
    void run();
    void start();
    void stop() {}
private:
	std::vector<Indicator *> mIndictors;
	std::vector<Rule *> mRrules;

private:
    void handleBreak();
    boost::asio::io_service m_io_service;
    boost::asio::signal_set m_signals;
};

}} // FQ_STRATEGY_STRATEGY_H

#endif /* FQ_STRATEGY_STRATEGY_H */
