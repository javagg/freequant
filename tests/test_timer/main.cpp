#include <iostream>

#include <fq/utils/timer.h>

using namespace FreeQuant::Utils;

int main(int argc,char* argv[]) {
    Timer timer(1);
    timer.start();
    sleep(5);
    return 0;
}
