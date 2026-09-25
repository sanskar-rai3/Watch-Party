#include <iostream>
#include "httplib.h"
#include "api/partyApi.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{

    httplib::Server svr;

    PartyServer party;

    party.registerRoutes(svr);

    svr.set_pre_routing_handler(
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

    svr.WebSocket(
        "/ws",
        [](const httplib::Request &req,
           httplib::ws::WebSocket &ws)
        {
            std::string msg;

            while (ws.read(msg))
            {
                try
                {
                    json data = json::parse(msg);

                    std::string type =
                        data.at("type").get<std::string>();

                    if (type == "join")
                    {
                        std::string name =
                            data.at("name").get<std::string>();

                        std::string roomId =
                            data.at("roomId").get<std::string>();

                        std::cout
                            << name
                            << " joined room "
                            << roomId
                            << "\n";

                        json response = {
                            {"type", "join_success"},
                            {"message", "Welcome " + name},
                            {"roomId", roomId}};

                        ws.send(response.dump());
                    }
                }
                catch (const std::exception &e)
                {
                    json error = {
                        {"type", "error"},
                        {"message", e.what()}};

                    ws.send(error.dump());
                }
            }
        });

    svr.Get("/", [](const httplib::Request &req, httplib::Response &res)
            { res.set_content("Hello world", "text/plain"); });

    std::cout << "http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}