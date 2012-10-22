#include "Instrument.h"

namespace FreeQuant {

Instrument::Instrument(std::string symbol, Instrument::Type type) :
    _symbol(symbol), _type(type){

}

} // namespace FreeQuant
