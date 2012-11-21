#ifndef FQ_DETAIL_BARRIER_H
#define FQ_DETAIL_BARRIER_H

#include <boost/thread/barrier.hpp>
#include <freequant/detail/Atomic.hpp>

namespace FreeQuant { namespace Detail {

class Barrier {
public:
    Barrier() : _barrier(2) {}
    void setActive(bool active) {
        _active.set(active);
    }

    bool active() const {
        return _active;
    }

    void wait() {
        if (active())
            _barrier.wait();
    }

private:
    Atomic<bool> _active;
    boost::barrier _barrier;
};

}} // namespace FreeQuant

#endif // FQ_DETAIL_BARRIER_H
