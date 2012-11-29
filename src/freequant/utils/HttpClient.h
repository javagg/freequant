#ifndef FQ_UTILS_HTTPCLIENT_H
#define FQ_UTILS_HTTPCLIENT_H

#include <string>

namespace FreeQuant {

class HttpClient {
public:
    HttpClient();
    ~HttpClient();
    std::string get(const std::string& url);
private:
    void *_curl;
};

} // namespace FreeQuant

#endif // FQ_UTILS_HTTPCLIENT_H
