#ifndef FQ_TRADE_TRADEPROVIDER_H
#define FQ_TRADE_TRADEPROVIDER_H

#include <string>
#include <vector>

namespace FreeQuant { namespace Trade {

class TradeProvider {
public:
    virtual ~TradeProvider() {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;

    virtual void logon() {}
    virtual void onLogon() {}
    virtual void logout() {}
    virtual void onLogout() {}
    virtual void onError() {}

    virtual std::vector<std::string> availableExchanges() const = 0;
    virtual std::vector<std::string> availableInstruments() const = 0;
//    virtual void subscribe(std::vector<std::string> symbols) = 0;
//    virtual void unsubscribe(std::vector<std::string> symbols) = 0;
};

}}

#endif // FQ_TRADE_TRADEPROVIDER_H
