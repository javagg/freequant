#include "MA.h"

namespace FreeQuant {
namespace Exp {

void MA::onCalculate(const FreeQuant::Bar& bar) {
    add(bar.close());
}

}}
