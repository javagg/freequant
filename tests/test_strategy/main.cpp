#include <functional>
#include <iostream>
#include <boost/thread.hpp>

#include <freequant/strategy/BaseStrategy.h>

int main() {
    FreeQuant::BaseStrategy strategy;
    strategy.setRunningMode(FreeQuant::BaseStrategy::Simulation);
    strategy.setRunningLength(10);
    strategy.start();
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    strategy.stop();
    return 0;
}
