#include <iostream>

#include <fq/strategy/strategy.h>
#include <fq/indicators/indicator.h>
#include <fq/indicators/ma.h>

using namespace std;

class DmaStrategy : public FreeQuant::Strategy::Strategy {
public:
    virtual void onInit() {
        addSymbol("IF1209");
        chooseMarketProvider("CTP");
        chooseTradeProvider("CTP");

        FreeQuant::Indicators::Indicator *ma = new FreeQuant::Indicators::MA();
        addIndicator(ma);

    }

    virtual void onExit() {

    }

    virtual void onStart() {

    }

    virtual void onStop() {

    }

    virtual void onBar(const FreeQuant::MarketData::Bar& bar) {

    }

};

int main() {
    DmaStrategy strategy;
    return strategy.exec();
}

