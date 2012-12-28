%module(directors="1") ctp

%include "typemaps.i"

%{
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
%}

%include "ThostFtdcUserApiDataType.h"
%include "ThostFtdcUserApiStruct.h"

%feature("director") CThostFtdcMdSpi;
%include "ThostFtdcMdApi.h"
%feature("director") CThostFtdcTraderSpi;
%include "ThostFtdcTraderApi.h"
