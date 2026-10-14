#include "video_state.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::string getVideoState(const Video& video) {
    json state = {
        {"type", "sync"},
        {"time", video.time},
        {"isPlaying", video.isPlaying}
    };

    return state.dump();
}
