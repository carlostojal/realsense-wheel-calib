#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>

enum errors_t {
    INVALID_RESOLUTION,
    INVALID_FRAMERATE,
    INVALID_FRAME_TYPE,
    INVALID_CAMERA_TYPE,
    ERROR_STARTING_STREAM,
    CALLBACK_NOT_SET
};

class Error {
    public:
        Error(errors_t error);
        errors_t error;
        std::string what();
};

#endif