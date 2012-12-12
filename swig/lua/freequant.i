%module freequant

%include "std_string.i"

%{
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/CtpMarketDataProvider.h>
using namespace FreeQuant;
%}

%include <freequant/marketdata/Bar.h>
%include <freequant/marketdata/Tick.h>
%include <freequant/marketdata/MarketDataProvider.h>
%include <freequant/marketdata/CtpMarketDataProvider.h>


