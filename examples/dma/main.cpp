#include <iostream>

#include <fq/strategy/strategy.h>

using namespace std;

class DmaStrategy : public FreeQuant::Strategy::Strategy {

};

int main() {
    DmaStrategy strategy;
    cout << "strategy run..." << endl;
    return strategy.run();
}

