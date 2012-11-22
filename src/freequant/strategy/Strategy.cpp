#include <memory>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/assign.hpp>
#include <boost/assign/std/vector.hpp>
#include <freequant/indicators/Indicator.h>
#include <freequant/trade/CtpTradeProvider.h>
#include <freequant/marketdata/BogusMarketDataProvider.h>
#include <freequant/utils/TimeSeries.h>

#include "Strategy.h"

using namespace std;
using namespace boost::assign;

namespace FreeQuant {

class StrategyMarketDataProvider : public MarketDataProvider {
public:
    explicit StrategyMarketDataProvider(Strategy *strategy = 0);
    ~StrategyMarketDataProvider() {}

    void setCallback(MarketDataProvider::Callback *callback) { _callback = callback; }
    void connect(bool block = true);
    void disconnect(bool block = true);
    bool isConnected() const { return _connected; }
    const std::string& name() const { return "Bogus"; }
    void subscribe(std::vector<std::string> symbols);
    void unsubscribe(std::vector<std::string> symbols);
    void generateBars();
private:
    bool _connected;
    std::set<std::string> _symbols;
    MarketDataProvider::Callback *_callback;
    Strategy *_strategy;
    std::shared_ptr<MarketDataGenerator> _mdGenerator;
};

class Strategy::MdProviderCallback : public DefaultMarketDataProviderCallback {
public:
    Strategy *_strategy;
    MdProviderCallback(Strategy *strategy) : _strategy(strategy) {}
    void onBar(const FreeQuant::Bar& bar) {
        _strategy->onMarketDataProviderBar(bar);
    }

    void onConnected() {
        _strategy->onMarketDataProviderConnected();
    }
};

class Strategy::TradeProviderCallback : public DefaultTradeProviderCallback {

};

Strategy::Strategy() : BaseStrategy(),
    _mdProvider(0), m_tradeProvider(0),
    _mdCallback(new Strategy::MdProviderCallback(this)),
    _tradeCallback(new Strategy::TradeProviderCallback()) {
}

Strategy::~Strategy() {
    delete _mdCallback; _mdCallback = 0;
    delete _tradeCallback; _tradeCallback = 0;
}

void Strategy::init() {
    BaseStrategy::init();

    vector<string> tsNames;
    tsNames += "open", "high", "low", "close", "volume";
//    for(auto i = tsNames.begin(); i != tsNames.end(); ++i) {
//        _tsMap[*i] = TimeSeriesPtr(new TimeSeries());
//    };
}

void Strategy::start() {
    if (_mdProvider)  {
        _mdProvider->connect();
        _mdProvider->subscribe(vector<string>(_symbols.begin(), _symbols.end()));
    }
    BaseStrategy::start();
}

void Strategy::stop() {
    BaseStrategy::stop();
    if (_mdProvider) _mdProvider->disconnect();
}

void Strategy::onStep() {
    BogusMarketDataProvider *provider = dynamic_cast<BogusMarketDataProvider*>(_mdProvider);
    provider->generateBars();
}

void Strategy::setTradeProvider(FreeQuant::TradeProvider *provider) {
    m_tradeProvider = provider;
}

void Strategy::setTradeProvider(std::shared_ptr<FreeQuant::TradeProvider> provider) {
    _tradeProvider = provider;
}

void Strategy::setMarketDataProvider(FreeQuant::MarketDataProvider *provider) {
    _mdProvider = provider;
    _mdProvider->setCallback(_mdCallback);
}

void Strategy::setMarketDataProvider(std::shared_ptr<FreeQuant::MarketDataProvider> provider) {
    _mdProvider = provider.get();
    _mdProvider->setCallback(_mdCallback);
}

FreeQuant::Task::TaskId Strategy::addTask(std::shared_ptr<FreeQuant::Task> task) {
    _tasks.push_back(task);
    return 0;
}

void Strategy::handleBar(const FreeQuant::Bar& bar) {
//    std::for_each(
//        m_indictors.begin(),
//        m_indictors.end(),
//        boost::bind(&Indicator::onBar, _1, bar)
//    );
}

void Strategy::addIndicator(Indicator *indicator) {
    m_indictors.push_back(indicator);
}

void Strategy::addIndicator(IndicatorPtr indicator) {
    _indicators.push_back(indicator);
}

void Strategy::addSymbols(const Symbols& symbols) {
    _symbols.insert(symbols.begin(), symbols.end());
}

void Strategy::onMarketDataProviderConnected() {
    std::cout << "onMarketDataProviderConnected: "  << std::endl;
}

void Strategy::onMarketDataProviderBar(const FreeQuant::Bar& bar) {
    BarSeries& bars = _barSeriesMap[bar.symbol()];
    bars.append(bar.dateTime(), bar);

    for (auto i = _indicators.begin(); i != _indicators.end(); ++i) {
        (*i)->onCalculate(bar);
    }
//    TimeSeriesPtr closeTs = _tsMap["close"];
//    closeTs->append(std::make_pair(bar.dateTime(), bar.close()));

//    for (auto i = _indicators.begin(); i != _indicators.end(); ++i) {
//        (*i)->append(bar.close());
//    }
    onBar(bar);
}

// Low-level order management functions
FreeQuant::Order *Strategy::createMarketOrder() {
    return nullptr;
}

FreeQuant::Order *Strategy::createStopOrder() {
    return nullptr;
}

FreeQuant::Order *Strategy::createLimitOrder() {
    return nullptr;
}

FreeQuant::Order *Strategy::createStopLimitOrder() {
    return nullptr;
}

void Strategy::buyMarket() {
    FreeQuant::Order *order = createMarketOrder();
    _tradeProvider->sendOrder(*order);
    delete order;
}

void Strategy::sellMarket() {}
void Strategy::buyStop() {}
void Strategy::sellStop() {}
void Strategy::buyStopLimit() {}
void Strategy::sellStopLimit() {}
void Strategy::buyLimit() {}
void Strategy::sellLimit() {}

FreeQuant::Order *createOrder(FreeQuant::Order::Type type, FreeQuant::Order::Side side,
    double price, long qty) {
    FreeQuant::Order *order = new FreeQuant::Order;
    return order;
}

} // namespace FreeQuant
