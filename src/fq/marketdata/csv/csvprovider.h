#ifndef FQ_MARKETDATA_CSV_CTPPROVIDER_H
#define FQ_MARKETDATA_CSV_CTPPROVIDER_H

#include <fq/marketdata/provider.h>

namespace FreeQuant { namespace MarketData {

class CsvProvider : public Provider {
public:
    CsvProvider();
    virtual ~CsvProvider();
    virtual void connect();
    virtual void disconnect();
    virtual bool isConnected();
};

}}

#endif // FQ_MARKETDATA_CSV_CTPPROVIDER_H
