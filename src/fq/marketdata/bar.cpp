#include "bar.h"

namespace FreeQuant { namespace MarketData {

Bar::Bar() {
}

Bar::Bar(double o, double h, double l, double c) : m_open(o), m_high(h), m_low(l), m_close(c) {}

}}
