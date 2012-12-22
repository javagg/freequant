%module(directors="1") freequant

%include "std_string.i"

%{
#include <freequant/utils/DateTime.h>
#include <freequant/marketdata/MarketDataProvider.h>
#include <freequant/marketdata/CtpMarketDataProvider1.h>
using namespace FreeQuant;
%}

%include <freequant/utils/DateTime.h>
%include <freequant/marketdata/Bar.h>
%include <freequant/marketdata/Tick.h>

%feature("director") MarketDataProvider;
%feature("director") MarketDataProviderCallback;
%include <freequant/marketdata/MarketDataProvider.h>
%include <freequant/marketdata/CtpMarketDataProvider1.h>


