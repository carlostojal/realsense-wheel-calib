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
        default:
            return "Unknown error";
    }
}