#include <iostream>

#include <fq/utils/Timer.h>
//#include <thread>

using namespace FreeQuant::Utils;

void onTimeout() {
    std::cout << "timeout!" << std::endl;
}

int main(int argc,char* argv[]) {
    FreeQuant::Utils::Timer timer(1);
    timer.connect(boost::bind(&onTimeout));
    timer.start();
//    sleep(5);
//    std::this_thread::sleep_for();
    return 0;
}
