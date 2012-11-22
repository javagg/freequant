#ifndef FQ_DETAIL_NOTIFIER_H
#define FQ_DETAIL_NOTIFIER_H

#include <functional>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace FreeQuant { namespace Detail {

class Notifier {
public:
    enum { ignorable = -1 };
    explicit Notifier() : _requestId(ignorable) {}

    template<typename Functor>
    void call(std::function<Functor>& func, int requestId = ignorable, bool block = true) {
        boost::unique_lock<boost::mutex> lock(_mutex);
        _requestId = requestId;
        _completed = false;
        _block = block;

        func();

        if (_block) {
            std::shared_ptr<boost::mutex> mutex(new boost::mutex());
            std::shared_ptr<boost::condition_variable> condition(new boost::condition_variable());
            auto pair = std::make_pair(_requestId, std::make_pair(mutex, condition));
            requests.insert(pair);
            while (!_completed) condition->wait(lock);
        }
    }

    void complete(int requestId = ignorable) {
        boost::unique_lock<boost::mutex> lock(_mutex);
        _completed = true;
        if ((_block) && (_requestId == requestId)) {
            auto i = requests.find(_requestId);
            if (i != requests.end()) {
                auto cond = (i->second).second;
                cond->notify_all();
                requests.erase(i);
            }
        }
    }

private:
    int _requestId;
    bool _completed;
    bool _block;
    boost::mutex _mutex;
    std::map<int, std::pair<std::shared_ptr<boost::mutex>, std::shared_ptr<boost::condition_variable> > > requests;
};

}}

#endif //FQ_DETAIL_NOTIFIER_H
