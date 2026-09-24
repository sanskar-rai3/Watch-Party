#include <iostream>
#include "httplib.h"
#include "api/partyApi.hpp"

int main()
{

    httplib::Server hSvr;

    hSvr.set_pre_routing_handler(
        [](const httplib::Request &req, httplib::Response &res)
        {
            res.set_header(
                "Access-Control-Allow-Origin",
                "http://localhost:3000");

            res.set_header(
                "Access-Control-Allow-Methods",
                "GET, POST, PUT, DELETE, OPTIONS");

            res.set_header(
                "Access-Control-Allow-Headers",
                "Content-Type");

            if (req.method == "OPTIONS")
            {
                res.status = 204;
                return httplib::Server::HandlerResponse::Handled;
            }

            return httplib::Server::HandlerResponse::Unhandled;
        });


    hSvr.Get("/", [](const httplib::Request &req, httplib::Response &res)
             { res.set_content("Hello world", "text/plain"); });

    hSvr.listen("0.0.0.0", 8080);

    return 0;
}