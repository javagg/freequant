#ifndef FQ_DETAIL_ATOMIC_HPP
#define FQ_DETAIL_ATOMIC_HPP

#include <freequant/FreeQuantPlatform.h>

#include <boost/thread/mutex.hpp>
#include <boost/utility.hpp>

namespace FreeQuant { namespace Detail {

template <class Tag>
struct UnsupportedTag;

template <typename T>
class Atomic {

};

template <>
class Atomic<bool> {
private:
    bool _value;
    mutable boost::mutex _mutex;
    Atomic(const Atomic&);
    Atomic& operator=(const Atomic&);
public:
    explicit Atomic() : _value(false) {}
    ~Atomic() {}

    void set(bool v) {
        boost::lock_guard<boost::mutex> _lock(_mutex);
        _value = v;
    }

    bool load(bool value) {
        boost::lock_guard<boost::mutex> _lock(_mutex);
        bool tmp = _value;
        _value = value;
        return tmp;
    }

    bool operator!() {
        boost::lock_guard<boost::mutex> _lock(_mutex);
        return !_value;
    }

    operator bool() const {
        boost::lock_guard<boost::mutex> _lock(_mutex);
        return static_cast<const volatile bool&>(_value);
    }
};

}} // namespace FreeQuant

#endif // FQ_DETAIL_ATOMIC_HPP
