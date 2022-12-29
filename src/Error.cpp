#include <realsense_wheel_calib/Error.h>

Error::Error(errors_t error) {
    this->error = error;
}

std::string Error::what() {
    switch(this->error) {
        case INVALID_RESOLUTION:
            return "Invalid resolution";
        case INVALID_FRAMERATE:
            return "Invalid framerate";
        case INVALID_FRAME_TYPE:
            return "Invalid frame type";
        case INVALID_CAMERA_TYPE:
            return "Invalid camera type";
        case CALLBACK_NOT_SET:
            return "The callback function was not set";
        case ERROR_STARTING_STREAM:
            return "Error starting stream";
        case ERROR_CREATING_THREAD:
            return "Error creating thread";
        case ERROR_DETACHING_THREAD:
            return "Error detaching thread";
        case ERROR_CANCELLING_THREAD:
            return "Error cancelling thread";
        case ERROR_GETTING_FRAMES:
            return "Error getting frames";
        case SOURCE_NOT_INITIALIZED:
            return "Source not initialized";
        default:
            return "Unknown error";
    }
}