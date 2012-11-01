#ifndef FQ_STRATEGY_STRATEGY_H
#define FQ_STRATEGY_STRATEGY_H

#include <memory>
#include <string>
#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <freequant/FreeQuantPlatform.h>
#include <freequant/marketdata/Bar.h>
#include <freequant/marketdata/Quote.h>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/strategy/Engine.h>
#include <freequant/strategy/Task.h>
#include <freequant/utils/DateTime.h>

namespace FreeQuant {
class TradeProvider;
class MarketDataProvider;
class Indicator;
}

namespace FreeQuant {

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
    typedef boost::shared_ptr<FreeQuant::Indicator> IndicatorPtr;
    typedef std::vector<IndicatorPtr> Indicators;

    typedef Task *TaskPtr;
    typedef std::vector<TaskPtr> Tasks;

    typedef boost::shared_ptr<FreeQuant::Order> OrderPtr;
    typedef std::vector<OrderPtr> Orders;

    typedef boost::shared_ptr<FreeQuant::Instrument> InstrumentPtr;
    typedef std::vector<InstrumentPtr> Instruments;

    typedef FreeQuant::MarketDataProvider MarketDataProvider;
    typedef FreeQuant::TradeProvider TradeProvider;
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
    virtual void onBar(const FreeQuant::Bar&) = 0;
    virtual void onQuote(const FreeQuant::Quote&) {}
    virtual void onTrade(const Trade&) {}
    virtual void onTask(const FreeQuant::DateTime dt) {}
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

    void addIndicator(FreeQuant::Indicator *indicator);
    void addInstrument(const Instrument& instrument) {}

    FreeQuant::Task::TaskId addTask(FreeQuant::Task task);
    void addSymbol(const std::string symbol) {}
    void addSymbols(std::vector<std::string>& symbols);

    void chooseTradeProvider(std::string name) {}
    void chooseMarketProvider(std::string name) {}

    void setTradeProvider(FreeQuant::TradeProvider *provider);
    void setMarketDataProvider(FreeQuant::MarketDataProvider *provider);

    std::vector<Exchange *>& exchanges() const {}
    std::vector<Instrument *>& instruments() const {}
    std::vector<Order *>& orders() const {}

    MarketDataProvider *marketDataProvider() const { return _mdProvider; }
    TradeProvider *tradeProvider() const { return m_tradeProvider; }
    OrderBook *orderBook() const { return 0; }

private:
    void start();
    void stop();

    void handleBar(const FreeQuant::Bar&);
    std::vector<FreeQuant::Indicator *> m_indictors;

    Indicators _indictors;
    Instruments _instruments;
    Orders _orders;
    Tasks _tasks;

    MarketDataProvider *_mdProvider;
    TradeProvider *m_tradeProvider;

    class MdProviderCallback;
    MdProviderCallback *_mdCallback;
    class TradeProviderCallback;
    TradeProviderCallback *_tradeCallback;
    std::set<std::string> _symbols;
};

} // FQ_STRATEGY_STRATEGY_H

#endif /* FQ_STRATEGY_STRATEGY_H */
