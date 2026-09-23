#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    svr.WebSocket("/ws", [](const httplib::Request &, httplib::ws::WebSocket &ws) {
        std::string msg;
        while (ws.read(msg)) {
            std::cout << msg << std::endl;
            ws.send(msg);
        }
    });

    std::cout << "Listening on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}