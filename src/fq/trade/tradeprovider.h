#ifndef FQ_TRADE_TRADEPROVIDER_H
#define FQ_TRADE_TRADEPROVIDER_H

#include <string>

namespace FreeQuant { namespace Trade {

class TradeProvider {
public:
    virtual ~TradeProvider() {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;

    virtual void login() {}
    virtual void onLogin() {}
    virtual void logout() {}
    virtual void onLogout() {}

};

}}

#endif // FQ_TRADE_TRADEPROVIDER_H
