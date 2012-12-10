%module(directors="1") freequant

%include typemaps.i
%include std_string.i
%include exception.i
%include carrays.i

%{
#include "../src/freequant/marketdata/CtpMarketDataProvider"
%}

%include "../src/freequant/marketdata/CtpMarketDataProvider"
