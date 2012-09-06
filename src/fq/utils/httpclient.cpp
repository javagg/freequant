#include "httpclient.h"

using namespace std;

namespace FreeQuant{ namespace Utils {

HttpClient::HttpClient() : curl(curl_easy_init()) {
}

HttpClient::~HttpClient() {
    curl_easy_cleanup(curl);
}

string HttpClient::get(string url) {
    std::string buffer;
    CURLcode res;

    res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res = curl_easy_perform(curl);

    return buffer;
}

}}
