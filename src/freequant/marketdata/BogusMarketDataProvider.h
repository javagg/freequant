#ifndef FQ_MARKETDATA_BOGUSPROVODER_H
#define FQ_MARKETDATA_BOGUSPROVODER_H

namespace FreeQuant {

class BogusMarketDataProvider {
public:
    BogusMarketDataProvider();
    ~BogusMarketDataProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected();
    virtual void onData();
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_BOGUSPROVODER_H
