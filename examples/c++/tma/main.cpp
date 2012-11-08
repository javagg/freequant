#include <iostream>
#include <memory>

#include <freequant/strategy/Strategy.h>
#include <freequant/marketdata/BogusMarketDataProvider.h>
#include <freequant/indicators/SMA.h>
#include <freequant/experiment/MA.h>

class DmaStrategy : public FreeQuant::Strategy {
private:
    typedef FreeQuant::Exp::MA MA;
    std::shared_ptr<MarketDataProvider> _mdProvider;
    std::shared_ptr<MA> ma;
public:
    void onInit() {
        std::cout << "strategy init..." << std::endl;
        setRunningMode(FreeQuant::Strategy::Simulation);
        setRunningLength(100);
        _mdProvider.reset(new FreeQuant::BogusMarketDataProvider(this));
        setMarketDataProvider(_mdProvider);
        std::vector<std::string> syms;
        syms.push_back("IF1210");
        addSymbols(syms);
        ma.reset(new MA(5));
        addIndicator(ma);
    }

    void onDestroy() {
        std::cout << "strategy destroy..." << std::endl;
    }

    void onStart() {
        std::cout << "strategy start..." << std::endl;
    }

    void onStop() {
        std::cout << "strategy exit..." << std::endl;
    }

    void onBar(const FreeQuant::Bar& bar) {
        std::cout << "bar: "<< bar << " sma: " << ma->last() << std::endl;
        auto bars = barSeries(bar.symbol());
        if (ma->crossAbove(bars, FreeQuant::Bar::Close)) {

        }
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
