#ifndef FQ_TRADE_FIXTRADEPROVIDER_H
#define FQ_TRADE_FIXTRADEPROVIDER_H

#include <fq/trade/tradeprovider.h>

namespace FreeQuant { namespace Trade {

class FixApp;

class FixTradeProvider : public TradeProvider {
public:
    FixTradeProvider();
    virtual ~FixTradeProvider() {}
    void connect();
    void disconnect();
    bool isConnected() const;
    std::string name() const { return "FIX"; }

    void sendOrder();
    void run();
private:
    FixApp *app;
};

}}
#endif // FQ_TRADE_FIXTRADEPROVIDER_H
