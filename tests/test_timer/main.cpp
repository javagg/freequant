#include <iostream>
#include <thread>

#include <fq/utils/Timer.h>

void onTimeout() {
    std::cout << "timeout!" << std::endl;
}

int main() {
    FreeQuant::Utils::Timer timer(1);
    timer.connect(boost::bind(&onTimeout));
    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
