#include "httpclient.h"

using namespace std;

namespace FreeQuant {

static int writer(char *data, size_t size, size_t nmemb, string *writerData) {
  if (writerData == NULL)
    return 0;

  writerData->append(data, size*nmemb);
  return size*nmemb;
}

HttpClient::HttpClient() : curl(curl_easy_init()) {
}

HttpClient::~HttpClient() {
    curl_easy_cleanup(curl);
}

string HttpClient::get(string url) {
    std::string buffer;
    CURLcode res;

    res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res = curl_easy_perform(curl);

    return buffer;
}

} // namespace FreeQuant
