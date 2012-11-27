#ifndef FQ_UTILS_HTTPCLIENT_H
#define FQ_UTILS_HTTPCLIENT_H

#include <string>
#include <pthread.h>

namespace FreeQuant {

class HttpClient {
public:
    HttpClient();
    ~HttpClient();
    std::string get(std::string url);
private:
    void *_curl;
};

} // namespace FreeQuant

#endif // FQ_UTILS_HTTPCLIENT_H
