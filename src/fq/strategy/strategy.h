/*!
 * \file strategy.h
 * \brief
 * \author
 */

#ifndef FQ_STRATEGY_STRATEGY_H
#define FQ_STRATEGY_STRATEGY_H

#include <memory>
#include <string>
#include <vector>

//#include <boost/asio/signal_set.hpp>

#include <boost/shared_ptr.hpp>

#include <fq/marketdata/bar.h>
#include <fq/marketdata/quote.h>
#include <fq/marketdata/marketdataprovider.h>
#include <fq/strategy/engine.h>
#include <fq/strategy/Task.h>
#include <fq/utils/datetime.h>

namespace FreeQuant {
    namespace Trade {
        class TradeProvider;
    }
    namespace MarketData {
        class MarketDataProvider;
        class MarketDataProvider;
    }
    namespace Indicators {
        class Indicator;
    }
}

namespace FreeQuant { namespace Strategy {

class Rule;
class Portfolio;
class Exchange;
class Trade;
class Order;
class OrderBook;
class Position;
class Instrument;

/*!
 * \class Strategy
 * \brief dddddddddd
 *
 * Detailed description starts here.
 */
class Strategy : public Engine {
public:
    typedef boost::shared_ptr<FreeQuant::Indicators::Indicator> IndicatorPtr;
    typedef std::vector<IndicatorPtr> Indicators;

    typedef Task *TaskPtr;
    typedef std::vector<TaskPtr> Tasks;

    typedef boost::shared_ptr<FreeQuant::Strategy::Order> OrderPtr;
    typedef std::vector<OrderPtr> Orders;

    typedef boost::shared_ptr<FreeQuant::Strategy::Instrument> InstrumentPtr;
    typedef std::vector<InstrumentPtr> Instruments;

    typedef FreeQuant::MarketData::MarketDataProvider MarketDataProvider;
    typedef FreeQuant::Trade::TradeProvider TradeProvider;
    /*!
     * \enum RunningMode
     * An enum type.
     * The documentation block cannot be put after the enum!
     */
    enum RunningMode {
        Simulation,
        Paper,
        Live
    };

    enum BarType {
        Tick,
        OneMinuent,
        FiveMinuents,
        TenMinuents,
        OneHour,
        OneDay,
        Custom
    };

    explicit Strategy();
	virtual ~Strategy();

    /*!
     * A pure virtual member.
     * \see testMe()
     * \param c1 the first argument.
     * \param c2 the second argument.
     */
    virtual void onBreak() {}
    virtual void onStart() {}
    virtual void onStop() {}
    virtual void onBar(const FreeQuant::MarketData::Bar&) = 0;
    virtual void onQuote(const FreeQuant::MarketData::Quote&) {}
    virtual void onTrade(const Trade&) {}
    virtual void onTask(const FreeQuant::Utils::DateTime dt) {}
    virtual void onOrderCreated(const Order&) {}
    virtual void onOrderFilled(const Order&) {}
    virtual void onOrderPartiallyFilled(const Order&) {}
    virtual void onOrderCancelled(const Order&) {}
    virtual void onOrderExpired(const Order&) {}
    virtual void onOrderRejected(const Order&) {}
    virtual void onOrderReplaced(const Order&) {}

    virtual void onPositionOpened(const Position& position) {}
    virtual void onPositionClosed(const Position& position) {}
    virtual void onPositionValueChanged(const Position& position) {}

    void addIndicator(FreeQuant::Indicators::Indicator *indicator);
    void addInstrument(const Instrument& instrument) {}

    FreeQuant::Strategy::Task::TaskId addTask(FreeQuant::Strategy::Task task);
    void addSymbol(const std::string symbol) {}
    void addSymbols(std::vector<std::string> symbols) {}

    void chooseTradeProvider(std::string name) {}
    void chooseMarketProvider(std::string name) {}

    void setTradeProvider(FreeQuant::Trade::TradeProvider *provider);
    void setMarketDataProvider(FreeQuant::MarketData::MarketDataProvider *provider);

    std::vector<Exchange *>& exchanges() const {}
    std::vector<Instrument *>& instruments() const {}
    std::vector<Order *>& orders() const {}

    MarketDataProvider *marketDataProvider() const { return m_mdProvider; }
    TradeProvider *tradeProvider() const { return m_tradeProvider; }
    OrderBook *orderBook() const {}

private:
    void start();
    void stop();

    void handleBar(const FreeQuant::MarketData::Bar&);
    std::vector<FreeQuant::Indicators::Indicator *> m_indictors;

    Indicators _indictors;
    Instruments _instruments;
    Orders _orders;
    Tasks _tasks;
    MarketDataProvider *m_mdProvider;
    TradeProvider *m_tradeProvider;
};

}} // FQ_STRATEGY_STRATEGY_H

#endif /* FQ_STRATEGY_STRATEGY_H */
