#include <iostream>

#include <fq/utils/timer.h>

using namespace FreeQuant::Utils;

void onTimeout() {
    std::cout << "timeout!" << std::endl;
}

int main(int argc,char* argv[]) {
    Timer timer(1);
    timer.connect(boost::bind(&onTimeout));
    timer.start();
//    sleep(5);
    return 0;
}
