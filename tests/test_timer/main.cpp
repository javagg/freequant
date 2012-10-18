#include <functional>
#include <iostream>
#include <boost/thread.hpp>

#include <freequant/utils/Timer.h>

void onTimeout() {
    std::cout << "timeout!" << std::endl;
}

int main() {
    FreeQuant::Timer timer(300, boost::bind(&onTimeout));
    timer.start();
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    return 0;
}
