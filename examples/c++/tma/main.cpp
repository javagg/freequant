#include <iostream>
#include <memory>

#include <freequant/strategy/Strategy.h>
#include <freequant/marketdata/BogusMarketDataProvider.h>

class DmaStrategy : public FreeQuant::Strategy {
private:
    boost::shared_ptr<MarketDataProvider> _mdProvider;
public:
    void onInit() {
        std::cout << "strategy init..." << std::endl;
        setRunningMode(FreeQuant::Strategy::Simulation);
        setRunningLength(10);
        _mdProvider.reset(new FreeQuant::BogusMarketDataProvider(this));
        setMarketDataProvider(_mdProvider);
        std::vector<std::string> syms;
        syms.push_back("IF1210");
        addSymbols(syms);
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
        std::cout << "bar: "<< bar << std::endl;
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
