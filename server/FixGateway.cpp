#include <iostream>
#include <string>

#include <quickfix/FileStore.h>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/Log.h>
#include <quickfix/ThreadedSocketAcceptor.h>
#include <quickfix/SessionSettings.h>

#include <freequant/server/Executor.h>
#include <freequant/fix/SocketAcceptor.h>

class Application : public FreeQuant::Executor {};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " FILE." << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    try {
        FIX::SessionSettings settings(filename);
        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FreeQuant::SocketAcceptor acceptor(application, storeFactory, settings, logFactory);
        acceptor.start();
        std::cout << "Type Ctrl-C to quit" << std::endl;
        while (true) {
            FIX::process_sleep(1);
        }
        acceptor.stop();
        return EXIT_SUCCESS;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
