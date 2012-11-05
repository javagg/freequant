#include "Engine.h"

namespace FreeQuant {

Engine::Engine() :
    _io_service(),
    _signal_set(_io_service, SIGINT, SIGTERM) {
}

int Engine::exec() {
    _signal_set.async_wait(std::bind(&Engine::onBreak, this));
    int ret = 0;
    while (true) {
        try {
            start();
            _io_service.run();
            stop();
            break;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            ret = -1;
        }
    }
    return ret;
}

} // namespace FreeQuant
