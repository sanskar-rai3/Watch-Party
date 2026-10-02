#include "application.hpp"

App::App()
    : partyapi_(partymanager_) {}

void App::start() {
    partyapi_.start(); 
}

