%module freequant

%include "std_string.i"

%{
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/CtpMarketDataProvider1.h>
using namespace FreeQuant;
%}

%include <freequant/utils/DateTime.h>
%include <freequant/marketdata/Bar.h>
%include <freequant/marketdata/Tick.h>
%include <freequant/marketdata/MarketDataProvider.h>
%include <freequant/marketdata/CtpMarketDataProvider1.h>


