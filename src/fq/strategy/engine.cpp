#include "engine.h"

namespace FreeQuant { namespace Strategy {

Engine::Engine() {
}

void Engine::start() {
    m_thread = new boost::thread(&Engine::run, this);
//    m_thread = new boost::thread(boost::bind(&Engine::run, this));
//    m_thread = new boost::thread([&] () {
//        run();
//    });
}

void Engine::run() {
    while (true) {
        if (!running) break;
    }
}

}}
