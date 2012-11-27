#ifndef FQ_DETAIL_NOTIFIER_H
#define FQ_DETAIL_NOTIFIER_H

#include <functional>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace FreeQuant { namespace Detail {

class Notifier {
public:
    enum { ignorable = -1 };
    explicit Notifier() {}

    template<typename Functor>
    void call1(std::function<Functor>& func, int requestId = ignorable, bool block = true) {
        boost::unique_lock<boost::mutex> lock(_mutex);
        std::shared_ptr<data> d(new data);
        d->requestId = requestId;
        d->completed = false;
        d->block = block;
        _requests.insert(std::make_pair(requestId, d));
        func();
        if (d->block) {
            d->cond.reset(new boost::condition_variable());
            while (!d->completed) d->cond->wait(lock);
        }
    }

    void complete1(int requestId = ignorable) {
        boost::unique_lock<boost::mutex> lock(_mutex);
        auto i = _requests.find(requestId);
        if (i != _requests.end()) {
            auto d = i->second;
            d->completed = true;
            if (d->block) {
                auto cond = d->cond;
                cond->notify_all();
            }
            _requests.erase(i);
        }
    }

private:
    struct data {
       int requestId;
       bool completed;
       bool block;
       std::shared_ptr<boost::condition_variable> cond;
    };

    boost::mutex _mutex;
    std::map<int, std::shared_ptr<data> > _requests;
};

}}

#endif //FQ_DETAIL_NOTIFIER_H
