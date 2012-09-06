#ifndef FQ_UTILS_HTTPCLIENT_H
#define FQ_UTILS_HTTPCLIENT_H

#include <string>
#include <curl/curl.h>

namespace FreeQuant{ namespace Utils {

class HttpClient {
public:
    HttpClient();
    ~HttpClient();
    std::string get(std::string url);
private:
    CURL *curl;
};

}}

#endif // FQ_UTILS_HTTPCLIENT_H
