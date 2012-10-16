#include <functional>
#include <iostream>
#include <thread>

#include <freequant/utils/Timer.h>

void onTimeout() {
    std::cout << "timeout!" << std::endl;
}

int main() {
    FreeQuant::Timer timer(300, std::bind(&onTimeout));
    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
