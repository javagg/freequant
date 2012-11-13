#include <functional>
#include <iostream>
#include <boost/thread.hpp>

#include <freequant/strategy/BaseStrategy.h>

int main() {
    class Strategy : public FreeQuant::BaseStrategy {
    public:
        virtual void onInit() {
            std::cout << __FUNCTION__ << std::endl;
            setRunningMode(FreeQuant::BaseStrategy::Simulation);
            setRunningLength(10);
        }

        virtual void onDestroy() {
            std::cout << __FUNCTION__ << std::endl;
        }

        virtual void onStart() {

            std::cout << __FUNCTION__ << std::endl;
        }

        virtual void onStop() {
            std::cout << __FUNCTION__ << std::endl;
        }

    protected:
        virtual void onStep() {
            std::cout << "Tick: " << runningTick() << std::endl;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
        }
    };

    Strategy strategy;
    strategy.init();
    strategy.start();
    while (strategy.running()) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    strategy.start();
    while (strategy.running()) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    strategy.destroy();
    return 0;
}
