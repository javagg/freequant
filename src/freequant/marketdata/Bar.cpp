#include "Bar.h"

namespace FreeQuant {

Bar::Bar(double open, double high, double low, double close, long volume) :
    _open(open), _high(high), _low(low), _close(close), _volume(volume) {
}

Bar::Bar(std::string s, FreeQuant::DateTime dt, double o, double h, double l, double c, long v) :
    _symbol(s), _end(dt), _open(o), _high(h), _low(l), _close(c), _volume(v) {
}

Bar& Bar::operator=(const Bar& bar) {
    if (this != &bar) {
        this->_symbol = bar._symbol;
        this->_end = bar._end;
        this->_open = bar._open;
        this->_high = bar._high;
        this->_low = bar._low;
        this->_close = bar._close;
        this->_volume = bar._volume;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const FreeQuant::Bar& bar) {
    os << "Symbol: " << bar.symbol() << "[open=" << bar.open() << "]" << std::endl;
    return os;
}

}
