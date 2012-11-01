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
    void onStart() {
        std::cout << "strategy start..." << std::endl;

        _mdProvider.reset(new FreeQuant::CtpMarketDataProvider());
        _mdProvider.reset(new FreeQuant::FixMarketDataProvider("host=127.0.0.1;port=7711;username=simuser;password=simuser"));
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

    void onStop() {
        std::cout << "strategy exit..." << std::endl;
    }

    void onBar(const FreeQuant::Bar& bar) {
        std::cout << "close: "<< bar.open() << std::endl;
        std::cout << "ma: "<< ma.value() << std::endl;
    }
};

int main() {
    DmaStrategy strategy;
    return strategy.exec();
}

