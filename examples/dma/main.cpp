#include <iostream>
#include <memory>

#include <fq/strategy/strategy.h>
#include <fq/indicators/indicator.h>
#include <fq/indicators/ma.h>
#include <fq/marketdata/marketdataprovider.h>
#include <fq/marketdata/ctp/ctpmarketdataprovider.h>
#include <fq/trade/tradeprovider.h>
#include <fq/trade/ctptradeprovider.h>

class DmaStrategy : public FreeQuant::Strategy::Strategy {
private:
    std::shared_ptr<FreeQuant::MarketData::MarketDataProvider> m_mdProvider;
    std::shared_ptr<FreeQuant::Trade::TradeProvider> m_tradeProvider;
    FreeQuant::Indicators::MA ma;
public:
    void onStart() {
        std::cout << "strategy start..." << std::endl;

        m_mdProvider.reset(new FreeQuant::MarketData::CtpMarketDataProvider());
        m_tradeProvider.reset(new FreeQuant::Trade::CtpTradeProvider());

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

    void onBar(const FreeQuant::MarketData::Bar& bar) {
        std::cout << "close: "<< bar.close() << std::endl;
        std::cout << "ma: "<< ma.value() << std::endl;
    }

};

int main() {
    DmaStrategy strategy;
    return strategy.exec();
}

