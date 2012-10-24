#include <iostream>
#include <memory>

#include <freequant/strategy/strategy.h>
#include <freequant/indicators/indicator.h>
#include <freequant/indicators/ma.h>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/ctp/ctpmarketdataprovider.h>
#include <freequant/trade/TradeProvider.h>
#include <freequant/trade/CtpTradeProvider.h>

class DmaStrategy : public FreeQuant::Strategy {
private:
    boost::shared_ptr<FreeQuant::MarketDataProvider> m_mdProvider;
    boost::shared_ptr<FreeQuant::TradeProvider> m_tradeProvider;
    FreeQuant::MA ma;
public:
    void onStart() {
        std::cout << "strategy start..." << std::endl;

        m_mdProvider.reset(new FreeQuant::CtpMarketDataProvider());
        m_tradeProvider.reset(new FreeQuant::CtpTradeProvider());

        addSymbol("IF1209");
        chooseMarketProvider("CTP");
        chooseTradeProvider("CTP");

        setMarketDataProvider(m_mdProvider.get());
        setTradeProvider(m_tradeProvider.get());

        addIndicator(&ma);
    }

    void onStop() {
        std::cout << "strategy exit..." << std::endl;
    }

    void onBar(const FreeQuant::Bar& bar) {
        std::cout << "close: "<< bar.close() << std::endl;
        std::cout << "ma: "<< ma.value() << std::endl;
    }

};

int main() {
    DmaStrategy strategy;
    return strategy.exec();
}

