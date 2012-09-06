#ifndef FQ_MARKETDATA_BOGUSPROVODER_H
#define FQ_MARKETDATA_BOGUSPROVODER_H

namespace FreeQuant { namespace MarketData {

class BogusProvoder {
public:
    BogusProvoder();
    ~BogusProvoder();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected();
    virtual void onData();
};

}}

#endif // FQ_MARKETDATA_BOGUSPROVODER_H
