#ifndef FQ_MARKETDATA_CSV_CTPPROVIDER_H
#define FQ_MARKETDATA_CSV_CTPPROVIDER_H

#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant { namespace MarketData {

class CsvProvider : public MarketDataProvider {
public:
    CsvProvider();
    virtual ~CsvProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected();
};

}}

#endif // FQ_MARKETDATA_CSV_CTPPROVIDER_H
