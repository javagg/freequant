#include <iostream>
#include <memory>

#include <freequant/strategy/Strategy.h>
#include <freequant/indicators/Indicator.h>
#include <freequant/indicators/MA.h>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/FixMarketDataProvider.h>
#include <freequant/marketdata/CtpMarketDataProvider.h>
#include <freequant/trade/TradeProvider.h>
#include <freequant/trade/CtpTradeProvider.h>

using namespace std;

class DmaStrategy : public FreeQuant::Strategy {
private:
    boost::shared_ptr<FreeQuant::MarketDataProvider> _mdProvider;
    boost::shared_ptr<FreeQuant::TradeProvider> _tradeProvider;
    FreeQuant::MA ma;
public:
    void onInit() {
        setRunningMode(Strategy::Live);
        _mdProvider.reset(new FreeQuant::CtpMarketDataProvider());
//        _mdProvider.reset(new FreeQuant::FixMarketDataProvider("senderid=ME;targetid=FQMarketDataServer;host=127.0.0.1;port=7711;username=simuser;password=simuser"));
        _tradeProvider.reset(new FreeQuant::CtpTradeProvider());

        vector<string> symbols;
        symbols.push_back("IF1212");
        symbols.push_back("GOOG");
        addSymbols(symbols);

        chooseMarketProvider("CTP");
        chooseTradeProvider("CTP");

        setMarketDataProvider(_mdProvider.get());
        setTradeProvider(_tradeProvider.get());

        addIndicator(&ma);
    }
    void onStart() {
        std::cout << "strategy start..." << std::endl;


    }

    void onStop() {
        std::cout << "strategy exit..." << std::endl;
    }

    void onBar(const FreeQuant::Bar& bar) {
        cout << "bar: "<< bar << endl;
    }

    void onDestroy() {
        std::cout << "strategy destroy..." << std::endl;
    }
};

int main() {
    DmaStrategy strategy;
    strategy.init();
    strategy.start();
    while (strategy.running()) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
    strategy.destroy();
}

