#include "Tick.h"

namespace FreeQuant {

std::ostream& operator<<(std::ostream& out, const FreeQuant::Tick& tick) {
    return out << "tick: timestamp=" << tick.datetime << " open=" << tick.open;
}

}
