#pragma once

#include <string>

struct Video {
    double time    = 0.0;
    bool isPlaying = false;
};

std::string getVideoState(const Video& video);
