%module(directors="1") freequant

%exceptionclass FreeQuant::Exception;

%include typemaps.i
%include std_string.i
%include exception.i
%include carrays.i

%{
#include "../src/freequant/Exceptions.h"
%}

