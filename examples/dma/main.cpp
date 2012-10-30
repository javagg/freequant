#include <iostream>
#include <memory>

#include <freequant/strategy/Strategy.h>
#include <freequant/indicators/Indicator.h>
#include <freequant/indicators/MA.h>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/CtpMarketDataProvider.h>
#include <freequant/trade/TradeProvider.h>
#include <freequant/trade/CtpTradeProvider.h>

class DmaStrategy : public FreeQuant::Strategy {
private:
    boost::shared_ptr<FreeQuant::MarketDataProvider> _mdProvider;
    boost::shared_ptr<FreeQuant::TradeProvider> _tradeProvider;
    FreeQuant::MA ma;
public:
    void onStart() {
        std::cout << "strategy start..." << std::endl;

        _mdProvider.reset(new FreeQuant::CtpMarketDataProvider());
        _tradeProvider.reset(new FreeQuant::CtpTradeProvider());

        addSymbol("IF1209");
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

