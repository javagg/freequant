#ifndef FQ_UTILS_HTTPCLIENT_H
#define FQ_UTILS_HTTPCLIENT_H

#include <string>

namespace FreeQuant {

class HttpClient {
public:
    HttpClient();
    ~HttpClient();
    const std::string& get(const std::string& url);
private:
    std::string buffer;
};

} // namespace FreeQuant

#endif // FQ_UTILS_HTTPCLIENT_H
