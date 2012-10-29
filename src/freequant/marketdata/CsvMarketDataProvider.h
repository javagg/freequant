#ifndef FQ_MARKETDATA_CSV_CTPPROVIDER_H
#define FQ_MARKETDATA_CSV_CTPPROVIDER_H

#include <freequant/marketdata/MarketDataProvider.h>

namespace FreeQuant {

class CsvMarketDataProvider : public MarketDataProvider {
public:
    CsvMarketDataProvider();
    virtual ~CsvMarketDataProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected();
};

} // namespace FreeQuant

#endif // FQ_MARKETDATA_CSV_CTPPROVIDER_H
