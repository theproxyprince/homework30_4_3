
#include <iostream>
#include <cpr/cpr.h>
#include <vector>


int main() {
    std::string key, value;
    std::vector<cpr::Pair> keys;
    while (true) {
        std::cout << "Enter key name: ";
        std::cin >> key;
        if (key == "post" || key == "get") break;
        std::cout << "Enter key value: ";
        std::cin >> value;
        keys.emplace_back(cpr::Pair(key, value));
    }

    if (key == "post") {
        cpr::Response r = cpr::Post(cpr::Url("https://httpbin.org/post"),
                                    cpr::Payload(keys.begin(),keys.end()));
        std::cout << r.text;
    } else {
        std::string getRequest = "https://httpbin.org/get?";
        for (auto& el : keys) {
            getRequest += '&' + el.key + '=' + el.value;
        }
        size_t pos = getRequest.find('&');
        getRequest.erase(pos,1);
        cpr::Response r = cpr::Get(cpr::Url(getRequest.c_str()));
        std::cout << r.text;
    }
    return 0;
}
