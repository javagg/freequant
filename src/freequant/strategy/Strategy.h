#ifndef FQ_STRATEGY_STRATEGY_H
#define FQ_STRATEGY_STRATEGY_H

#include <memory>
#include <string>
#include <set>
#include <vector>

#include <memory>


#include <freequant/Config.h>
#include <freequant/marketdata/Bar.h>
#include <freequant/marketdata/Tick.h>
#include <freequant/marketdata/Quote.h>
#include <freequant/utils/DateTime.h>
#include <freequant/strategy/BaseStrategy.h>
#include <freequant/strategy/Task.h>
#include <freequant/strategy/Order.h>
#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/TimeSeries.h>
#include <freequant/marketdata/TickCompressor.h>

namespace FreeQuant {

class Account;
class MarketDataProvider;
class TradeProvider;
class Indicator;
class Portfolio;
class Trade;
class OrderBook;
class Position;
class Instrument;

/*!
 *  \class Strategy
 *  \brief dddddddddd
 *
 *  Detailed description starts here.
 */
class Strategy : public BaseStrategy {
public:
    typedef std::shared_ptr<Exp::Indicator> IndicatorPtr;
    typedef std::vector<IndicatorPtr> Indicators;

    typedef std::shared_ptr<Task> TaskPtr;
    typedef std::vector<TaskPtr> Tasks;

    typedef std::shared_ptr<Order> OrderPtr;
    typedef std::vector<OrderPtr> Orders;

    typedef std::shared_ptr<Instrument> InstrumentPtr;
    typedef std::vector<InstrumentPtr> Instruments;

    typedef FreeQuant::MarketDataProvider MarketDataProvider;
    typedef FreeQuant::TradeProvider TradeProvider;

//    typedef FreeQuant::Exp::TimeSeries<Bar> BarSeries;
    typedef Exp::TimeSeries<Tick> TickSeries;
    typedef Exp::TimeSeries<Trade> TradeSeries;

    typedef std::map<std::string, BarSeries> BarSeriesMap;
    typedef std::vector<std::string> Symbols;

    enum CommissionType { PerShare, Percent, Absolute };
    enum MarketDataType	{ MdTrade, MdTick, MdBar, MdMarketDepth };

    explicit Strategy();
	virtual ~Strategy();

    void onInit() {}
    void onDestroy() {}

    /*!
     *  onStart – called when strategy first starts up, before the first bar
     */
    void onStart() {}

    /*!
     *  onStop – called when the strategy shuts down, after the last bar
     */
    void onStop() {}

    void init();
    void start();
    void stop();

    /*!
     * A pure virtual member.
     * \see testMe()
     * \param c1 the first argument.
     * \param c2 the second argument.
     */

    virtual void onProviderConnected(const std::string& provider) {}
    virtual void onProviderDisconnected(const std::string& provider) {}
    virtual void onProviderError(const std::string& provider) {}

    virtual void onBarOpen(const Bar&) {}
    virtual void onBar(const Bar&) {}
    virtual void onTick(const Tick&) {}
    virtual void onQuote(const Quote&) {}
    virtual void onTrade(const Trade&) {}
    virtual void onTask(const DateTime&) {}
    virtual void onOrderCreated(const Order&) {}
    virtual void onOrderFilled(const Order&) {}
    virtual void onOrderPartiallyFilled(const Order&) {}
    virtual void onOrderCancelled(const Order&) {}
    virtual void onOrderExpired(const Order&) {}
    virtual void onOrderRejected(const Order&) {}
    virtual void onOrderReplaced(const Order&) {}

    /*!
     *  OnPositionOpened - fired whenever a new position is established as a result of
     *  a completed trade.
     */
    virtual void onPositionOpened(const Position& position) {}
    virtual void OnPositionChanged(const Position& position) {}
    virtual void onPositionClosed(const Position& position) {}

    /*!
     * \brief onPositionValueChanged - fired whenever a new incoming trade price changes
     *                                 the value of a position.
     * \param position
     */
    virtual void onPositionValueChanged(const Position& position) {}

    void addIndicator(Indicator *indicator);
    void addIndicator(IndicatorPtr indicator);
    void addInstrument(const Instrument& instrument) {}

    Task::TaskId addTask(std::shared_ptr<Task> task);
    void removeTask(Task::TaskId taskId);

    void addSymbols(const Symbols& symbols);
    void removeSymbols(const Symbols& symbols);
    const Symbols& symbols() const;

    void chooseTradeProvider(std::string name) {}
    void chooseMarketProvider(std::string name) {}

    void setTradeProvider(TradeProvider *provider);
    void setTradeProvider(std::shared_ptr<TradeProvider> provider);
    void setMarketDataProvider(MarketDataProvider *provider);
    void setMarketDataProvider(std::shared_ptr<MarketDataProvider> provider);

    const Instruments& instruments() const { return _instruments; }
    const Orders& orders() const { return _orders; }
    const Orders& orders(Order::Status status) const { return _orders; }
    const Orders& orders(std::string symbol) const { return _orders; }

    bool hasPosition() const { return false; }
    MarketDataProvider *marketDataProvider() const { return _mdProvider; }
    TradeProvider *tradeProvider() const { return m_tradeProvider; }
    OrderBook *orderBook() const { return 0; }

    BarSeries *createBarSeries();
//    const BarSeries& barSeries() const { return _barSeries; }
    const BarSeries& barSeries(const std::string symbol) {
        return _barSeriesMap[symbol];
    }

    Trade *lastTrade(const std::string& symbol);

    long position(std::string symbol) { return 0; }
    void clearPositions();
    void clearPosition(std::string symbol);
    void cancelOrders();

    // Low-level order management functions
    Order *createMarketOrder();
    Order *createStopOrder();
    Order *createLimitOrder();
    Order *createStopLimitOrder();

    // High-level order management functions;
    void buyMarket();
    void sellMarket();
    void buyStop();
    void sellStop();
    void buyStopLimit();
    void sellStopLimit();
    void buyLimit();
    void sellLimit();

    Account *account() { return nullptr; }

private:
    Order *createOrder(Order::Type type, Order::Side side, double price, long qty);
    void onStep();
    virtual void onMarketDataProviderConnected();
    void onMarketDataProviderTick(const Tick&);
    void accumulateTicks(const std::vector<Tick>&);
    std::vector<Indicator *> m_indictors;

    TickCompressor<Tick, Bar> compressor;
    Indicators _indicators;
    Instruments _instruments;
    Orders _orders;
    Tasks _tasks;

    MarketDataProvider *_mdProvider;
    TradeProvider *m_tradeProvider;

    std::shared_ptr<TradeProvider> _tradeProvider;
    class MdProviderCallback;
    class TradeProviderCallback;
    friend class MdProviderCallback;
    friend class TradeProviderCallback;
    MdProviderCallback *_mdCallback;
    TradeProviderCallback *_tradeCallback;
    std::set<std::string> _symbols;

    TickSeries _tickSeries;
    BarSeries _barSeries;
    BarSeriesMap _barSeriesMap;
};

} // FQ_STRATEGY_STRATEGY_H

#endif /* FQ_STRATEGY_STRATEGY_H */
