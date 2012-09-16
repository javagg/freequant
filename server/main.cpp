#include <iostream>
#include <fstream>
#include <string>

#include <quickfix/FileStore.h>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/Log.h>
#include <quickfix/SessionSettings.h>
#include <fq/server/executor.h>

class Application : public FreeQuant::Server::Executor {
public:
    Application() {}
};

void wait() {
    std::cout << "Type Ctrl-C to quit" << std::endl;
    while(true) {
        FIX::process_sleep(1);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0]
                  << " FILE." << std::endl;
        return 0;
    }

    std::string file = argv[1];

    try {
        FIX::SessionSettings settings(file);
        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FIX::SocketAcceptor acceptor(application, storeFactory, settings, logFactory );

        acceptor.start();
        wait();
        acceptor.stop();
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
